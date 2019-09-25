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
const int inf = 0x7f7f7f7f;

struct edge{int v,nxt;};
struct Graph{
	edge e[N<<1];
	int h[N],tot;
	int dis[N];
	inline void add(int x,int y)
	{
		e[++tot] = (edge){y,h[x]};
		h[x] = tot;
	}	
}G1,Gn;//求1到所有点最小路径值，求所有点到n的最大路径值 
int vis[N],n,m,w[N];
queue<int> q;
inline void spfa(Graph G,int *dis,int st,int mode)
{
	if(mode==2) up(i,1,n) dis[i] = inf;
	up(i,1,n) vis[i] = 0;
	dis[st] = w[st];
	q.push(st);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		Auto(i,x)
		{
			int v = G.e[i].v;
			if(mode == 1)//求路径最大值 
			{
				int d = max(dis[x],w[v]);
				if(dis[v] < d)
				{
					dis[v] = d;
					if(!vis[v]) q.push(v),vis[v] = 1;
				}				
			}
			else//求路径最小值 
			{
				int d = min(dis[x],w[v]);
				if(dis[v] > d)
				{
					dis[v] = d;
					if(!vis[v]) q.push(v),vis[v] = 1;
				}	 
			}
		}
	}
}
int a,b,c;
int main()
{
	io >> n >> m;
	up(i,1,n) io >> w[i];
	up(i,1,m)
	{
		io >> a >> b >> c;
		if(c==2) 
		{
			G1.add(a,b),G1.add(b,a);
			Gn.add(a,b),Gn.add(b,a);
		}
		else G1.add(a,b),Gn.add(b,a);
	}
	spfa(G1,G1.dis,1,2);
	spfa(Gn,Gn.dis,n,1);
	int ans = 0;
	up(i,1,n)
	{
		ans = max(ans, Gn.dis[i]-G1.dis[i]);
	}
	io << ans;
	return 0;
}
