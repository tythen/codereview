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
#define Auto(i,x) for(register int i=G.h[x];i;i=G.e[i].nxt)
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
const ll inf = 0x7f7f7f7f7f7f7f7f;

struct edge{int v,nxt;ll w;};
struct Graph{
	edge e[N<<1];
	int h[N],tot;
	ll dis[N];
	inline void add(int x,int y,ll w)
	{
		e[++tot] = (edge){y,h[x],w};
		h[x] = tot;
	}	
}G;
int vis[N],n,m1,m2;
deque <int> q;
inline void spfa(Graph G,ll *dis,int st)
{
	up(i,1,n) vis[i] = 0,dis[i] = inf;
	dis[st] = 0;
	q.push_front(st);
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		Auto(i,x)
		{
			int v = G.e[i].v;
			if(dis[v] > dis[x] + G.e[i].w)
			{
				dis[v] = dis[x] + G.e[i].w;
				if(!vis[v]) 
				{
					vis[v]=1;
					if(!q.empty() && dis[v] < dis[q.front()]) q.push_front(v);
					else q.push_back(v);
				}
			}
		}
	}
}
int a,b,c,st;

int main()
{
	io >> n >> m1 >> m2 >> st;
	up(i,1,m1)
	{
		io >> a >> b >> c;
		G.add(a,b,c),G.add(b,a,c);
	}
	up(i,1,m2)
	{
		io >> a >> b >> c;
		G.add(a,b,c);
	}
	spfa(G,G.dis,st);
	up(i,1,n)
	{
		if(G.dis[i] == inf) puts("NO PATH");
		else io << G.dis[i] << '\n';
	}
	return 0;
}
