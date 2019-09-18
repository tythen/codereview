#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
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
const int N = 2e5+5;
struct edge{
	int v,nxt;
}e[N<<2];
int tot,h[N];
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}

int dep[N],pre[20][N];
ll c[N];
inline void dfs(int x,int f){
	dep[x] = dep[f] + 1,pre[0][x] = f;
	for(int i=1;(1<<i)<=dep[x];i++)  pre[i][x] = pre[i-1][pre[i-1][x]];
	for(int i=h[x];i;i=e[i].nxt){
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
	}
}
inline int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=log2(dep[x])+1;i>=0;i--) if(dep[pre[i][x]] >= dep[y]) x = pre[i][x];
	if(x==y) return x;
	for(int i=log2(dep[x])+1;i>=0;i--)
		if(pre[i][x] != pre[i][y])
			x = pre[i][x],y = pre[i][y];
	return pre[0][x];
}
inline void dfs2(int x,int f){
	for(int i=h[x];i;i=e[i].nxt){
		int v = e[i].v;
		if(v==f) continue;
		dfs2(v,x);
		c[x] += c[v];
	}	
}


int n,m,a,b;
int main(){
	io >> n >> m;
	for(int i=1;i<n;i++)
		io >> a >> b,add(a,b),add(b,a);
	dfs(1,0);
	for(int i=1;i<=m;i++)
	{
		io >> a >> b;
		c[a]++,c[b]++;
		c[lca(a,b)]-=2;
	}
	ll ans1 = 0,ans2 = 0;
	dfs2(1,0);
	for(int i=2;i<=n;i++){
		if(c[i]==0) ans1++;
		else if(c[i]==1) ans2++;
	}
	io << ans1*m + ans2;
	return 0;
}
