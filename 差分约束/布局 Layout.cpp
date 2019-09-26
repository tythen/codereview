#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<limits>

#define ll long long
#define ull unsigned ll
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=a;i>=b;--i)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x){
		re char c=getchar();int f=1;x=0;
		for(;!isa(c);c=getchar()) if(c=='-') f=-1;
		for(;isa(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x){
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
const ll inf = 0x7f7f7f7f;
/*
a-b >= c ==> add(b,a,c) 
a-b <= c ==> add(a,b,c) 
a-b == c ==> add(a,b,c) , add(b,a,c) 
a[n]最大 跑最短路 , a[n]最小 跑最长路 
理由就是求最小时，我们跑最长路，假如跑完后还有更小的，
那么在跑最长路时一定还会对其进行松弛，使其变得更大，所以我们跑完最长路后，一定不会还存在更小的了。求最大的也同样的道理

可恶题面有迷惑行为：
奶牛从小到大排： 
a-b >= c ==> add(b,a,c) 
a-b <= c ==> add(a,b,c) 
a-b == c ==> add(a,b,c) , add(b,a,c) 
同时1到n最远 跑最短路 
*/
const int N = 2e5+5;
struct edge{int v,nxt;ll w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,ll w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int n,m1,m2,vis[N],cnt[N];
ll dis[N];
deque <int> q;
inline bool spfa(int st)
{
	up(i,1,n) dis[i] = inf,vis[i] = 0;
	q.push_front(st);
	dis[st] = 0;
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		cnt[x]++;
		if(cnt[x] >= n) return 1;
		
		Auto(i,x)
		{
			int v = e[i].v;
			if(dis[v] > dis[x] + e[i].w)//跑最短路 
			{
				dis[v] = dis[x] + e[i].w;
				if(!vis[v])
				{
					vis[v] = 1;
					if(!q.empty() && dis[v] < dis[q.front()]) q.push_front(v);
					else q.push_back(v);
					q.push_back(v);
				}
			}
		}
	}
	
	return 0;
}
int a,b,c;
int main()
{
	io >> n >> m1 >> m2;
	up(i,1,m1)
	{
		io >> a >> b >> c;
		add(a,b,c);
	}
	up(i,1,m2)
	{
		io >> a >> b >> c;
		add(b,a,-c);
	}
	up(i,1,n) add(0,i,0);
	int ans1 = spfa(0);
	int ans2 = spfa(1);
	if(ans1 && ans2) io <<-1;
	else if(dis[n]==inf) io << -2;
	else io << dis[n];
	return 0;
}
