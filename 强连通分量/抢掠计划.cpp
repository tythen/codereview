#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long 
#define re register

#define up(i,a,b) for(register int i=a;i<=b;i++) 
#define down(i,a,b) for(register int i=a;i>=b;i--)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt) 
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
const int N = 5e5+5;
const int inf = 0x7f7f7f7f;
struct node{int x,y;}oe[N];
struct edge{
	int v,nxt;
}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int low[N],dfn[N],idx,stk[N],top,vis[N];
int col[N],cnt;
int mon[N],w[N],isbar[N],isbar2[N];
inline void tarjan(int x){
	low[x] = dfn[x] = ++idx;
	stk[++top] = x;
	vis[x] = 1;
	Auto(i,x)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[x] = min(low[v],low[x]);
		}
		else if(vis[v]) low[x] = min(low[x],low[v]);
	}
	if(low[x] == dfn[x])
	{
		cnt++;
		while(stk[top] != x){
			col[stk[top]] = cnt;
			if(isbar[stk[top]]) isbar2[cnt] = 1;
			w[cnt] += mon[stk[top]];
			vis[stk[top--]] = 0;
		}
		col[stk[top]] = cnt;
		if(isbar[stk[top]]) isbar2[cnt] = 1;
		w[cnt] += mon[stk[top]];
		vis[stk[top--]] = 0;		
	}
}
ll ans = 0;
int a,b;
int n,m,p,s;
int fa[N];
inline int find(int x){return fa[x] == x?x:fa[x] = find(fa[x]);}
inline void dfs(int x,int f){
	vis[x] = 1;
	Auto(i,x)
	{
		int v=e[i].v;
		if(vis[v]) continue; 
		if(v!=f) dfs(v,x);
	}
}
int in[N];
ll dp[N];
queue <int> q;
inline void topsort()
{
	dfs(col[s],0);
	up(i,0,n) h[i] = 0,fa[i] = i;tot = 0;
	up(i,1,m)
	{
		if(col[oe[i].x]!=col[oe[i].y] && vis[col[oe[i].x]] && vis[col[oe[i].y]])
		{
			add(col[oe[i].x],col[oe[i].y]);
			in[col[oe[i].y]]++;
		}
	}//由于指定起点所以把有用的点先dfs出来再重新建边 
	q.push(col[s]);
	while(!q.empty())
	{
		int x = q.front();q.pop();
		dp[x] += w[x];
		Auto(i,x)
		{
			int v = e[i].v;
			in[v]--;
			dp[v] = max(dp[x],dp[v]);
			if(!in[v]) q.push(v);
		}
	}	
}

int main()
{
	io >> n >> m;
	up(i,1,m)
	{
		io >> oe[i].x >> oe[i].y;
		add(oe[i].x, oe[i].y);
	}
	up(i,1,n) io >> mon[i];
	io >> s >> p;
	up(i,1,p) io >> a,isbar[a] = 1;
	up(i,1,n) if(!dfn[i]) tarjan(i);
	
	up(i,0,n) h[i] = 0,fa[i] = i;
	tot = 0;
	up(i,1,m)
		if(col[oe[i].x]!=col[oe[i].y])
			add(col[oe[i].x],col[oe[i].y]);
			
	topsort();
	up(i,1,cnt) if(isbar2[i]) ans = max(ans,dp[i]);
	io << ans;
	return 0;
}
