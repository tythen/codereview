#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define re register
using namespace std;
struct ios{
	inline char fchar(){
		static char buf[100000],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
	}
//	#define getchar fchar
	template <typename ty> inline ios& operator >> (ty &x)
	{
		register int f=1;x=0;register char c=getchar();
		for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
		for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
		x*=f;return *this;
	}
	template <typename ty>  inline ios& operator << (ty x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
const int N = 2e4+5;
struct edge{int v,nxt,w;}e[N<<1];
int tot,h[N];
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int n;
int lg[N],pre[20][N],dep[N],dis[N];
inline void dfs(int x,int f)
{
	dep[x] = dep[f] + 1;
	pre[0][x] = f;
	for(int i=1;(1<<i)<=dep[x];i++) pre[i][x] = pre[i-1][pre[i-1][x]];
	for(int i=h[x];i;i=e[i].nxt)
	{
		int v = e[i].v;
		if(v==f) continue;
		dis[v] = dis[x] + e[i].w;
		dfs(v,x);
	}
}
inline int lca(int x,int y)
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=lg[dep[x]];i>=0;i--) if(dep[pre[i][x]] >= dep[y]) x = pre[i][x];
	if(x==y) return x;
	for(int i=lg[dep[x]];i>=0;i--)
		if(pre[i][x]!=pre[i][y])
			x=pre[i][x], y=pre[i][y];
	return pre[0][x];
}


int m,a,b,c;
int main()
{
	io >> n >> m;
	for(int i=2;i<=n;i++) lg[i] = lg[i>>1] + 1;
	for(int i=1;i<n;i++)
	{
		io >> a >> b >> c;
		add(a,b,c),add(b,a,c);
	}
	dfs(1,0);
	while(m--)
	{
		io >> a >> b;
		io << dis[a] + dis[b] - 2*dis[lca(a,b)] << '\n';
	}
	return 0;
}
