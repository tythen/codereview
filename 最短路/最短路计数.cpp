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
const int mod = 100003;
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
}G1,G2;
int vis[N],n,m;
deque <int> q;
int cnt[N];
inline void spfa(Graph G,ll *dis,int st,int mode=0)
{
	up(i,1,n) vis[i] = 0,dis[i] = inf;
	dis[st] = 0;cnt[st]=1;
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
			if(mode)
			{
				if(G1.dis[v] == dis[x]+G.e[i].w) cnt[v] += cnt[x];
				cnt[v] %= mod;
			}			
		}
	}
}
int a,b,c,st;

int main()
{
	io >> n >> m;
	up(i,1,m)
	{
		io >> a >> b;
		if(a==b) continue;
		G1.add(a,b,1),G1.add(b,a,1);
		G2.add(a,b,1),G2.add(b,a,1);
	}
	spfa(G1,G1.dis,1);
	spfa(G2,G2.dis,1,1);
	up(i,1,n)
	{
		io << cnt[i] << '\n';
	}
	return 0;
}
