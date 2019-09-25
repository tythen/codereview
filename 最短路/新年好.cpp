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

const int N = 1e5+5;
const int inf = numeric_limits<int>::max();
struct edge{int v,nxt,w;};
struct Graph{
	edge e[N<<1];
	int h[N],tot;
	int dis[N];
	inline void add(int x,int y,int w)
	{
		e[++tot] = (edge){y,h[x],w};
		h[x] = tot;
	}
}G[6];
struct node{
	int x;ll dis;
	friend bool operator < (const node a,const node b){
		return a.dis > b.dis;
	}
};
priority_queue <node> q;

int vis[N];
int n,m;
inline void dijkstra(Graph &G,int st,int *dis)
{
	up(i,1,n) dis[i] = 0x7f7f7f7f,vis[i] = 0;
	dis[st] = 0;
	q.push((node){st,dis[st]});
	while(!q.empty())
	{
		int x = q.top().x;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		Auto(i,x,G)
		{
			int v = G.e[i].v;
			if(dis[v] > dis[x] + G.e[i].w)
			{
				dis[v] = dis[x] + G.e[i].w;
				q.push((node){v,dis[v]});
			}
		}
	}
	dis[st] = inf;
}

int a,b,c;
int num[10];
int toG[N];
inline ll sovle()
{
	ll ret = 0;
	ret += G[0].dis[num[1]];
	ret += G[toG[num[1]]].dis[num[2]];
	ret += G[toG[num[2]]].dis[num[3]];
	ret += G[toG[num[3]]].dis[num[4]];
	ret += G[toG[num[4]]].dis[num[5]];	
	return ret;
}
int main()
{
	io >> n >> m;
	up(i,1,5) io >> num[i];num[0]=1;
	up(i,1,m)
	{
		io >> a >> b >> c;
		up(j,0,5) G[j].add(a,b,c),G[j].add(b,a,c);
	}
	up(i,0,5) 
	{
		toG[num[i]] = i;
		dijkstra(G[i],num[i],G[i].dis);
		printf("%d:",num[i]);up(j,1,n) io << G[i].dis[j] << ' ';puts("");
	}
	ll ans = inf;
	up(i,1,120)
	{
		ans = min(ans,sovle());
		next_permutation(num+1,num+1+5);
	}
	io << ans;	
	return 0;
}
