#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
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
const int N = 5e5+5;
int lg[N];
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y)
{
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}

int pre[20][N];
int dep[N];
inline void dfs(int x,int f)
{
	dep[x] = dep[f]+1;
	pre[0][x] = f;
	for(int i=1;(1<<i)<=dep[x];i++) pre[i][x] = pre[i-1][pre[i-1][x]];
	for(int i=h[x];i;i=e[i].nxt)
	{
		int v = e[i].v;
		if(v==f) continue;
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
			x=pre[i][x],y=pre[i][y];
	return pre[0][x];
	
}

int n,m,s,a,b;
int main()
{
	io >> n;
	for(int i=2;i<=n;i++) lg[i] = lg[i>>1] + 1;
	for(int i=1;i<n;i++)
	{
		io >> a >> b;
		add(a,b),add(b,a);
	}
	dfs(1,0);
	io >> m;
	for(int i=1;i<=m;i++)
	{
		io >> a >> b;
		io << dep[a] + dep[b] - 2*dep[lca(a,b)] << '\n';
	}
	return 0;
}
