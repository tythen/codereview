#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

#define ll long long
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
	inline int rd(){int x;*this >> x;return x;}
}io;
const int N = 8e6+5;
struct edge{int v,nxt;ll w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
struct Trie{
	int son[N][12],totrt;
	ll end[N];
	inline void insert(ll s)
	{
		int rt = 0;
		down(i,32,0)
		{
			int v = (s>>i) & 1;
			if(!son[rt][v]) son[rt][v] = ++totrt;
			rt = son[rt][v];
		}
		end[rt] = s;
	}
	inline ll find(ll s)
	{
		int rt = 0;
		ll ans = 0;
		down(i,32,0)
		{
			int v = (s>>i) & 1;
			if(son[rt][v^1]) rt = son[rt][v^1],ans += (1<<i);
			else rt = son[rt][v];
		}
		return ans;
	}
}t;
int n,m;
ll u,v,w;
ll ans;
int a[N];
inline void dfs(int x,int f,int now)
{
	t.insert(now);
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x, now^e[i].w);
	}
}
inline void dfs1(int x,int f,int now)
{
	ans = max(ans, t.find(now));
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs1(v,x, now^e[i].w);
	}
}
int main()
{
	io >> n;
	up(i,1,n-1)
	{
		io >> u >> v >> w;
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0,0);
	dfs1(1,0,0);
	io << ans;
	return 0;
}
