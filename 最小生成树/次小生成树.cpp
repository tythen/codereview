#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>

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
const int N = 1e6+5;
const ll inf = 99999999999;
struct node{int u,v;ll w;}oe[N<<1];
int fa[N];
inline int find(int x){return fa[x]==x? x:fa[x] = find(fa[x]);}
inline bool cmp(node a,node b){return a.w < b.w;}

struct edge{int v,nxt;ll w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,ll w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int pre[23][N],dep[N],fath[N];
ll spmax[23][N],pmax[23][N];//严格次小生成树要存次大值！ 
inline void dfs(int x,int f)
{
	fath[x] = f,dep[x] = dep[f]+1;
	pre[0][x] = f;
	for(int i=1;(1<<i) <= dep[x];i++)
	{
		pre[i][x] = pre[i-1][pre[i-1][x]];
		pmax[i][x] = max(pmax[i-1][x], pmax[i-1][pre[i-1][x]]);
		spmax[i][x] = max(spmax[i-1][x], spmax[i-1][pre[i-1][x]]);
		if(pmax[i-1][x]!=pmax[i-1][pre[i-1][x]])//保证次小 
			spmax[i][x] = max(min(pmax[i-1][x],pmax[i-1][pre[i-1][x]]), spmax[i][x]);//我一开始写了个min(min())像个憨批一样 
	}
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		pmax[0][v] = e[i].w;
		spmax[0][v] = -inf;
		dfs(v,x);
	}
}
inline int lca(int x,int y)
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=log2(dep[x])+1;i>=0;i--) 
		if(dep[pre[i][x]] >= dep[y]) 
			x = pre[i][x];
	if(x==y) return x;
	for(int i=log2(dep[x])+1;i>=0;i--)
		if(pre[i][x] != pre[i][y])
			x = pre[i][x],y = pre[i][y];			
	return pre[0][x];
}
inline ll qmax(int x,int y,ll smer)//以后这种树上倍增我都分开写好了，先求lca，函数式 
{
	ll Max = -inf;
	for(int i=log2(dep[x])+1;i>=0;i--) 
		if(dep[pre[i][x]] >= dep[y]) 
		{
			if(pmax[i][x] != smer) Max = max(Max,pmax[i][x]);
			else Max = max(Max,spmax[i][x]);
			x = pre[i][x];
		}
	return Max;
}
ll sum = 0;
int n,m,a,b,c,vis[N];
int main()
{
	io >> n >> m;
	up(i,1,m)
	{
		io >> a >> b >> c;
		oe[i] = (node){a,b,c};
	}
	up(i,1,n) fa[i] = i;
	sort(oe+1,oe+1+m,cmp);
	for(register int i=1,cnt=0;i<=m;i++)
	{
		int fx = find(oe[i].u),fy = find(oe[i].v);
		if(fx==fy) continue;
		fa[fy] = fx;
		add(oe[i].u,oe[i].v,oe[i].w);
		add(oe[i].v,oe[i].u,oe[i].w);
		cnt++;
		vis[i] = 1;
		sum += oe[i].w;
		if(cnt == n-1) break;
	}
	dfs(1,0);
	ll ans = inf;
	up(i,1,m)
	{
		if(vis[i]) continue;
		int LCA = lca(oe[i].u,oe[i].v);
		ll lmax = qmax(oe[i].u,LCA,oe[i].w);
		ll rmax = qmax(oe[i].v,LCA,oe[i].w);
		ll nans = sum - max(lmax, rmax) + oe[i].w;
		ans = min(ans,nans);
	}
	io << ans;
	return 0;
}
