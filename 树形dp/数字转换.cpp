#include<bits/stdc++.h>

#define re register
#define ll long long
#define isa(c) (c>='0'&&c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i) 
#define Auto(i,x) for(register int i=h[x];i;i = e[i].nxt)

using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		x=0;int f=1;register char c=getchar();
		for(;!isa(c);c=getchar()) if(c=='-') f=-1;
		for(;isa(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) *this << x/10;
		putchar(x%10+48);
	}
	inline ios& operator << (char x){putchar(x);}
}io;
const int N = 5e4+5;
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y)
{
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int dp[N],ans;
int vis[N];
inline void dfs(int x,int f)
{
	vis[x] = 1;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		ans = max(ans,dp[x] + dp[v] + 1);
		dp[x] = max(dp[x],dp[v] + 1);
	}
}

int sum[N],n;	
int main()
{
	io >> n;
	for(int i=1;i<=n;i++)
		for(int j=2;j*i<=n;j++)
			sum[j*i] += i;
	for(int i=2;i<=n;i++)
	{
		if(sum[i] >= i) continue;
		add(sum[i],i);//只存在大数向小数连边，显然是一颗树
		add(i,sum[i]);
	}
	dfs(1,0);
	printf("%d",ans);
	return 0;
}
