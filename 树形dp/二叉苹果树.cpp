#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define ll long long
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=b;i>=a;--i)
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
	inline int rd(){
		int x;*this >> x;return x;
	}
}io;
const int N = 500;
struct edge{int v,nxt,w;}e[N];
int h[N],tot;
inline void add(int x,int y,int w){
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
} 
int w[N];
ll dp[N][N];
int n,q;
inline void dfs(int x,int f)
{
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		up(i,1,q)//子树x总共的树枝 
		{
			up(j,0,i)//分给子树v的树枝 
			{
				dp[x][i] = max(dp[x][i],dp[v][i-j-1] + e[i].w);
			}
		}
	}
}
int a,b,c;
int main()
{
	io >> n >> q;
	up(i,1,n)
	{
		io >> a >> b >> c;
		add(a,b,c),add(b,a,c);
	}
	dfs(1,0);
	io << dp[1][q];
	return 0;
}
