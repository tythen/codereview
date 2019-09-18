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
const int N = 8e3+5;
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
int spy[N],cost[N],w[N],spy2[N];
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
	if(low[x] == dfn[x]){
		cnt++;
		while(stk[top] != x){
			col[stk[top]] = cnt;
			if(spy[stk[top]]) spy2[cnt] = 1;
			w[cnt] = min(w[cnt],cost[stk[top]]);
			vis[stk[top--]] = 0;
		}
		col[stk[top]] = cnt;
		if(spy[stk[top]]) spy2[cnt] = 1;
		w[cnt] = min(w[cnt],cost[stk[top]]);
		vis[stk[top--]] = 0;		
	}
}
inline void dfs(int x,int f)
{
	vis[x] = 1;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		if(!vis[v]) dfs(v,x);
	}
}
int in[N];
int a,b;
int n,m,p;
int main(){
	io >> n >> p;
	memset(w,0x7f,sizeof w);
	memset(cost,0x7f,sizeof cost);
	up(i,1,p)
	{
		io >> a >> b;
		spy[a] = 1;
		cost[a] = b;
	}
	io >> m;
	up(i,1,m)
	{
		io >> oe[i].x >> oe[i].y;
		add(oe[i].x,oe[i].y);
	}
	up(i,1,n) if(!dfn[i]) tarjan(i);
	up(i,0,n) h[i] = 0;
	tot = 0;
	up(i,1,m) if(col[oe[i].x] != col[oe[i].y]) in[col[oe[i].y]]++,add(col[oe[i].x],col[oe[i].y]);
	ll ans = 0;
	up(i,1,cnt){
		if(!in[i]){
			if(spy2[i] == 0) ans = -9999999999999;
			else ans += w[i];
		}
	}
	if(ans < 0)
	{
		puts("NO");
		up(i,1,n) if(!vis[i] && spy2[i]) dfs(i,0);
		up(i,1,n)
		{
			if(vis[col[i]]==0)
			{
				io << i;
				return 0;
			}
		}
	}
	else 
	{
		puts("YES");
		io << ans;
	}
	return 0;
}
