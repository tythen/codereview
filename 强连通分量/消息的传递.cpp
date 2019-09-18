#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define re register
#define ll long long

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
const int N = 1e3+5;
struct node{int x,y;}oe[N*N];
struct edge{
	int v,nxt;
}e[N*N];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int low[N],dfn[N],stk[N],vis[N],top,idx;
int col[N],cnt;
inline void tarjan(int x){
	low[x] = dfn[x] = ++idx;
	stk[++top] = x;
	vis[x] = 1;
	Auto(i,x){
		int v = e[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x],low[v]);
		}else if(vis[v]) low[x] = min(low[x],low[v]);
	}
	if(dfn[x] == low[x]){
		cnt++;
		while(stk[top]!=x){
			int v = stk[top--];
			col[v] = cnt;
			vis[v] = 0;
		}
		int v = stk[top--];
		col[v] = cnt;
		vis[v] = 0;		
	}
}
int n,m;
int in[N],a;
int g[1005][1005];
int main(){
	io >> n;
	up(i,1,n) up(j,1,n) 
	{
		io >> g[i][j];
		if(g[i][j]) add(i,j),oe[++m] = (node){i,j};
	}
	up(i,1,n) if(!dfn[i]) tarjan(i);
	up(i,1,m){
		if(col[oe[i].x] != col[oe[i].y]){
			in[col[oe[i].y]]++;
		}
	}
	int ans=0;
	up(i,1,cnt){
		if(!in[i]) ans++;
	}
	io << ans;
	return 0;
}
