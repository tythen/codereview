#include<bits/stdc++.h>
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
#define up(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
template <typename ty> inline void read(ty &x){
	x=0;int f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
const int N = 2e3+5;
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int dp[N][2];//dp[][1]表示自己放一个，dp[][0]表示自己不放
inline void dfs(int x,int f)
{
	dp[x][1]=1,dp[x][0]=0;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		dp[x][1] += min(dp[v][1],dp[v][0]);
		dp[x][0] += dp[v][1];
	}
}

int n,k,a,b;
int main()
{
	read(n);
	up(i,1,n)
	{
		read(a),read(k);a++;
		while(k--){read(b);b++;add(a,b),add(b,a);}
	}
	dfs(1,0);
	printf("%d",min(dp[1][0],dp[1][1]));
	return 0;
}
