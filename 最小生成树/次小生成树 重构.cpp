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
#define int ll 
const int N = 5e5+5;
//const ll inf = 0x7f7f7f7f7f7f7f7f; 
const ll inf = numeric_limits <ll> ::max() / 2; //OHHHHHHH这里一定要开大！！！！！，开到比longlong'max小一点或者1/2才可以 
struct node{int x,y;ll w;}oe[N<<1];
inline bool cmp(node a,node b){
	return a.w < b.w;
}
struct edge{int v,nxt;ll w;}e[N<<1];
int tot,h[N];
inline void add(int x,int y,ll w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int fa[N];
inline int find(int x){return x==fa[x]? x : fa[x] = find(fa[x]);}
int n,m,vis[N];
inline ll kruskal()
{
	ll ret = 0;
	up(i,1,n) fa[i] = i;
	for(int i=1,cnt = 0;i<=m;i++)
	{
		int fx = find(oe[i].x),fy = find(oe[i].y);
		if(fx==fy) continue;
		fa[fy] = fx;
		ret += oe[i].w;
		add(oe[i].x,oe[i].y,oe[i].w);
		add(oe[i].y,oe[i].x,oe[i].w);
		cnt++;
		vis[i] = 1;
		if(cnt == n-1) break;
	}
	return ret;
}
ll pmax[23][N],spmax[23][N];
int pre[23][N],dep[N];
inline void dfs(int x,int f)
{
	dep[x] = dep[f] + 1;
	for(int i=1;(1<<i) <= dep[x];i++)
	{
		pre[i][x] = pre[i-1][pre[i-1][x]];
		if(pre[i-1][x] >= N) exit(19);
		pmax[i][x] = max(pmax[i-1][x],pmax[i-1][pre[i-1][x]]);
		spmax[i][x] = max(spmax[i-1][x],spmax[i-1][pre[i-1][x]]);
		if(pmax[i-1][x] ^ pmax[i-1][pre[i-1][x]])
			spmax[i][x] = max(min(pmax[i-1][x],pmax[i-1][pre[i-1][x]]),spmax[i][x]);
	}
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		pre[0][v] = x;
		pmax[0][v] = e[i].w;
		spmax[0][v] = -inf;
		dfs(v,x);
	}
}
inline int getlca(int x,int y)
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=log2(dep[x]);i>=0;i--)
		if(dep[pre[i][x]] >= dep[y]) x = pre[i][x];
	if(x==y) return x;
	for(int i=log2(dep[x]);i>=0;i--)
		if(pre[i][x] != pre[i][y])
			x = pre[i][x],y = pre[i][y];
	return pre[0][x];
}
inline ll qmax(int x,int y,ll smaller)
{
	ll Max = -inf;
	for(int i=log2(dep[x]);i>=0;i--)
	{
		if(dep[pre[i][x]] >= dep[y])
		{
			if(smaller != pmax[i][x]) Max = max(Max,pmax[i][x]);
			Max = max(Max,spmax[i][x]);
			x = pre[i][x];
		}
	}
	return Max;
}
ll ans = inf;
signed main()
{
	io >> n >> m;
	up(i,1,m)
		io >> oe[i].x >> oe[i].y >> oe[i].w;
	sort(oe+1,oe+1+m,cmp);
	ll MST = kruskal();
	dfs(1,0);
	up(i,1,m)
	{
		if(vis[i]) continue;
		int x = oe[i].x, y = oe[i].y;
		int lca = getlca(x,y);
		ll lmax = qmax(x,lca,oe[i].w);
		ll rmax = qmax(y,lca,oe[i].w);
		ll cut = max(lmax,rmax);
		ll nans = MST + oe[i].w - cut;
		if(nans ^ MST) ans = min(nans,ans);
	}
	io << ans;
	return 0;
}
