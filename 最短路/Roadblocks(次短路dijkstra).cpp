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
const int N = 2e5+5;
const int inf = numeric_limits <int> :: max();
struct edge{int v,nxt;ll w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,ll w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
struct node{
	int x;ll dis;
	friend bool operator < (const node a,const node b){return a.dis > b.dis;}
};
priority_queue <node> q;
int vis[N],n,m;
ll dis[N],dis2[N];
inline void dijkstra(int st)
{
	up(i,1,n) dis[i] = dis2[i] = inf,vis[i] = 0;
	dis[st] = 0;
	q.push((node){st,dis[st]});
	while(!q.empty())
	{
		int x = q.top().x;
		ll ndis = q.top().dis;//注意与普通dij的区别：不写vis，只用结构体的dis更新 
		q.pop();
		Auto(i,x)
		{
			int v = e[i].v;
			ll tdis = ndis + e[i].w;
			if(dis[v] > tdis)//如果可以更新最短路 
			{
				dis2[v] = dis[v];
				dis[v] = tdis;
				q.push((node){v,dis[v]});
			}
			if(dis2[v] > tdis && tdis > dis[v])//如果只能更新次短路 
			{
				dis2[v] = tdis;
				q.push((node){v,dis2[v]});//可能存在不能更新最短路而可以更新次短路的情况，也就是从这个节点开始一直到n都是次短路，如果只更新最短路就没法延伸到n去 
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
		add(a,b,c);
		add(b,a,c);
	}
	dijkstra(1);
	io << dis2[n];
	return 0;
}
