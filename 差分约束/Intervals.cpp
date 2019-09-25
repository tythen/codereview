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
[a,b]c
做前缀和 
		s[b] - s[a-1] >= c  ===> s[a-1] <= s[b]-c   add(s[b],s[a-1],-c)
另外有：
		s[k] - s[k-1] <= 1  ===> s[k] <= s[k-1]+1   add(s[k-1],s[k],1)
*/
struct edge{int v,nxt,w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}


deque <int> q;
int dis[N],vis[N],n;
int maxr = 0;
inline void spfa(int st)
{
	up(i,1,maxr) dis[i] = -inf, vis[i] = 0;
	dis[st] = 0;
	q.push_front(st);
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		Auto(i,x)
		{
			int v = e[i].v;
			if(dis[v] < dis[x] + e[i].w)
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
}



int a,b,c;
int main()
{
	io >> n;
	up(i,1,n)
	{
		io >> a >> b >> c;
		maxr = max(maxr,b);
		add(a,b+1,c);//s[b+1] - s[a] <= c  ===>  s[b+1]  <= c + s[a]
	}
	up(i,0,maxr) 
	{
		//s[i+1] - s[i] <= 0/1   ===> s[i+1] <= 0/1 + s[i]
		add(i,i+1,0);//从正方向走+1的代价为0, 
		add(i+1,i,-1);//因为走得是正方向，所以绝对不能往回，在最长路时不会走负边 
	}
	spfa(0);
	io << dis[maxr+1];
	return 0;
}
