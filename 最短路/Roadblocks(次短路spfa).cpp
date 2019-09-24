#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>

#define ll long long
#define ull unsigned ll
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=a;i>=b;--i)
#define Auto(i,x,G) for(register int i=G.h[x];i;i=G.e[i].nxt)
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
/*
次短路模板
我记不得了，网上冲浪了一下
spfa的最好懂最好写：2O(spfa) + m
*/
const int N = 2e5+5;
struct edge{int v,nxt;ll w;};
struct node{int x,y;ll w;}oe[N<<1];
struct Graph{
	edge e[N<<1];
	int h[N],tot;
	ll dis[N];
	inline void add(int x,int y,ll w)
	{
		e[++tot] = (edge){y,h[x],w};
		h[x] = tot;
	}
}G1,G2;
deque <int> q;
int vis[N];
int n,m;
inline void spfa(Graph &G,int st,ll *dis)
{
	up(i,1,n) dis[i] = 0x7f7f7f7f,vis[i] = 0;
	dis[st] = 0;
	q.push_front(st);
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		Auto(i,x,G)
		{
			int v = G.e[i].v;
			if(dis[v] > dis[x] + G.e[i].w)
			{
				dis[v] = dis[x] + G.e[i].w;
				if(!vis[v])
				{
					vis[v] = 1;
//					if(!q.empty() && dis[v] <= dis[q.front()]) q.push_front(v);
//					else q.push_back(v);
					q.push_back(v);
				}
			}
		}
	}
}


ll a,b,c;
int main()
{
	io >> n >> m;
	up(i,1,m)
	{
		io >> a >> b >> c;
		oe[i].x = a,oe[i].y = b,oe[i].w = c;
		G1.add(a,b,c);
		G1.add(b,a,c);
		G2.add(a,b,c);
		G2.add(b,a,c);//都是双向图！ 
	}
	spfa(G1,1,G1.dis);
	spfa(G2,n,G2.dis);
	ll ans = 0x7f7f7f7f;
	ll shortest = G1.dis[n];
	up(i,1,m)
	{
		if(G1.dis[oe[i].x] + G2.dis[oe[i].y] + oe[i].w != shortest)//都是双向图！ 
			ans = min(ans, G1.dis[oe[i].x] + G2.dis[oe[i].y] + oe[i].w);//都是双向图！ 
		if(G1.dis[oe[i].y] + G2.dis[oe[i].x] + oe[i].w != shortest)//都是双向图！ 
			ans = min(ans, G1.dis[oe[i].y] + G2.dis[oe[i].x] + oe[i].w);//都是双向图！ 
	}
	io << ans;
	return 0;
}
