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
	inline int rd(){int x;*this >> x;return x;}
}io;
const int N = 5e6+5; 
struct edge{
	int v,nxt;
}e[N<<1];
int h[N],tot;
inline void add(int x,int y)
{
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int w[N],dp[N][2];
inline void dfs(int x,int f)
{
	dp[x][1] = w[x];
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		dp[x][1] += dp[v][0];
		dp[x][0] += max(dp[v][1],dp[v][0]);
	}
}
int n,a,b;
int in[N];
int main()
{
	io >> n;
	up(i,1,n) io >> w[i];
	up(i,1,n-1) io >> a >> b,add(b,a),in[a]++;
	io >> a >> b;
	up(i,1,n)
	{
		if(!in[i])
		{
			dfs(i,0);
			io << max(dp[i][1],dp[i][0]);
			return 0;
		}
	}
	
	return 0;
}
