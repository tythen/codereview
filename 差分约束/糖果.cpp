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
const int N = 5e5+5;
const int inf = 0x7f7f7f7f;
/*
差分约束：
我模型套反了！
 
*/
struct edge{int v,nxt,w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int dis[N],vis[N],n,cnt[N];
deque <int> q;
int maxr = 0;
inline ll spfa(int st)
{
//	for(int i=n;i>=1;i--)
	up(i,1,n)
	{
		dis[i] = 1, vis[i] = 1 , cnt[i] = 0;
		q.push_back(i);
//		dis[i] = -inf;
	}
//	dis[st] = 0;
//	q.push_front(st);//绝了我建了超级原点就过不了 
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		cnt[x]++;
		if(cnt[x] >= n) 
		{
			puts("-1");
			exit(0);
		}
		Auto(i,x)
		{
			int v = e[i].v;
			if(dis[v] < dis[x] + e[i].w)//是找最长路哦 
			{
				dis[v] = dis[x] + e[i].w;
				if(!vis[v])
				{
					vis[v] = 1;
					if(!q.empty() && dis[v] > dis[q.front()]) q.push_front(v);
					else q.push_back(v);
				}
			}
		}
	}
	ll ans = 0;
	up(i,1,n) ans += dis[i];
//	up(i,1,n) io << dis[i] <<' ';puts("");
	return ans;
}
int a,b,c,m;
int main()
{
//	freopen("candy5.in","r",stdin);
	io >> n >> m;
	while(m--)
	{
		io >> c >> a >> b;
		switch(c)
		{
			case 1: add(a,b,0),add(b,a,0);break;
			case 2: add(a,b,1);break;
			case 3: add(b,a,0);break;
			case 4: add(b,a,1);break;
			case 5: add(a,b,0);break;
		}
		if(c%2==0 && a==b)
		{
			puts("-1");
			return 0;
		}
	}
	up(i,1,n) add(0,i,1);
	io << spfa(0);
	return 0;
}
