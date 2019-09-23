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
}io;
/*
最小生成树：选最便宜的点 
*/
const int N = 500000;
struct node{int u,v,w;}ee[N];
int tot;
int e[505][505];
int fa[N],n,w[N];
inline int find(int x){return x==fa[x] ? x : fa[x] = find(fa[x]);}
inline bool cmp(node a,node b){return a.w < b.w;}
int main()
{
	freopen("water.3.in","r",stdin);
	io >> n;
	up(i,1,n) io >> w[i],fa[i] = i;
	up(i,1,n) up(j,1,n) io >> e[i][j];
	up(i,1,n) up(j,i+1,n) ee[++tot] = (node){i,j,e[i][j]};
	sort(ee+1,ee+1+tot,cmp);
	int ans = 0;
	for(int i=1,cnt=0;i<=tot;i++)
	{
		int fx = find(ee[i].u),fy = find(ee[i].v);
		if(fx == fy) continue;
		ans += ee[i].w;
		fa[fy] = fx;
		cnt++;
//		if(cnt == n-1) break;
	}
	int minpoint = 0x7f7f7f7f;
	up(i,1,n) minpoint = min(minpoint,w[i]);
	io << minpoint + ans;
	return 0;
}
