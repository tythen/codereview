#include<bits/stdc++.h>

#define ll long long
#define up(i,a,b) for(register int i=a;i<=b;i++)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
#define re register
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		x = 0;int f = 1;register char c=getchar();
		for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
		for(;isdigit(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
const int N = 2e6+5;
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int dia = 0,s;
inline void dfs(int x,int f,int dis)
{
	if(dis > dia) dia = dis,s = x;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x,dis+1);
	}
}
int d[N],ans[N];//表示过这个点的最长链 
inline void dp(int x,int f)
{
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dp(v,x);
		if(d[x] + d[v] + 1 == dia) ans[x] = ans[v] = 1;
		d[x] = max(d[x],d[v]+1);
	}
}

int a,b,n;
int main()
{
	io >> n;
	up(i,1,n-1)
	{
		io >> a >> b;
		add(a,b),add(b,a);
	}
	dfs(0,-1,0);
	dfs(s,-1,0);
	dp(0,-1);
	up(i,0,n-1) if(ans[i]) io << i << '\n';
	return 0;
}
