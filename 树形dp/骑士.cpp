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
int h[N],tot = 1;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
vector <int> loop;
int fa[N],dfn[N],idx,onloop[N];
int ban_edge,eu,ev;
inline void getloop(int x,int fath)
{
	dfn[x] = ++idx;
	fa[x] = fath;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==fath) continue;
		if(!dfn[v]) getloop(v,x);//他这个找环是断边 
		else
		{
			ban_edge =i;
			eu = x,ev = v;			
		}
	}
}

ll a,b,w[N],dp[N][2],ban[N],n;
inline void dfs(int x,int f)
{
	dp[x][1] = w[x],dp[x][0] = 0;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f || i==ban_edge || i==(ban_edge^1)) continue;
		dfs(v,x);
		dp[x][0] += max(dp[v][1],dp[v][0]);
		dp[x][1] += dp[v][0];
	}
}
ll ans;
int main()
{
	io >> n;
	up(i,1,n)
	{
		io >> w[i] >> a;
		add(a,i),add(i,a);
	}
	up(i,1,n)
	{
		if(!dfn[i])//图可能不连通 那么只能存在基环树 
		{
			loop.clear();
			getloop(i,0);
			ll tmp = 0;
			dfs(eu,0);
			tmp = max(tmp,dp[eu][0]);//因为对面点不知道选没选，所以先认为这个点没选 
			dfs(ev,0);
			tmp = max(tmp,dp[ev][0]);			
			ans += tmp;
		}
	}
	io << ans;
	return 0;
}
