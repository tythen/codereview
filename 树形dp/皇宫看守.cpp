#include<iostream>
#include<cstdio>
#include<cmath>
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
	inline int rd(){
		int x;*this >> x;return x;
	}
}io;
const int N = 3e5+5;
struct edge{int v,nxt;}e[N];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int dp[N][3],w[N];
inline void dfs(int x,int f)
{
	int sum=0;dp[x][1] = w[x];
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		dp[x][0] += min(dp[v][1],dp[v][2]);//这个位置由父亲放：儿子要么自己放，要么儿子的儿子放
		dp[x][1] += min(min(dp[v][0],dp[v][1]),dp[v][2]);//自己放了，儿子由任意一个情况转移而来
		sum += min(dp[v][1],dp[v][2]);//先计算所有儿子都自由的情况 
	}
	dp[x][2] = 0x7f7f7f7f;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;//我们必须抓一个儿子来强行放一个，保证自己由儿子覆盖 
		dp[x][2] = min(dp[x][2],sum - min(dp[v][1],dp[v][2]) + dp[v][1]);//当然这里是选最小的 
	}	
}
int a,b,c;
int n;
int main()
{
	io >> n;
	up(i,1,n)
	{
		io >> a;io >> w[a];io >> c;
		while(c--){io >> b;add(a,b),add(b,a);}
	}
	dfs(1,0);
	io << min(dp[1][1],dp[1][2]);
	return 0;
}
