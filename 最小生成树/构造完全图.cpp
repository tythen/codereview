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
/*
通过最小生成树得到完全图上两点之间的边长 
用计数原理加 
*/
const int N = 1e5+5;
struct edge{
	int w,v,nxt;
}e[N<<1];
int h[N],tot;
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){w,y,h[x]};
	h[x] = tot;
}
int size[N],n;
ll ans;
inline void dfs(int x,int f)
{
	size[x] = 1;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		size[x] += size[v];
		ans += (size[v] * (n-size[v])) * (e[i].w+1);
	}
}

int a,b,c;
int main()
{
	io >> n;
	up(i,1,n-1)
	{
		io >> a >> b >> c;
		add(a,b,c),add(b,a,c);
	}
	dfs(1,0);
	io << ans;
	return 0;
}
