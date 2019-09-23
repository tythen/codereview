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
最小k个生成树， 
求d值（最大值）最小，想到二分
用并查集 
*/
const int N = 4000000;
const double eps = 1e-6;
struct node{int x,y;}p[N];
struct edge{int u,v;double dis;}e[N];
int tot;
int fa[N],n,k;
inline int find(int x){return x==fa[x] ? x : fa[x] = find(fa[x]);}
inline bool check(double d)
{
	up(i,1,n) fa[i] = i;
	for(int i=1;i<=tot && e[i].dis < d-eps;i++)
	{
		int fx = find(e[i].u),fy = find(e[i].v);
		if(fx == fy) continue;
		fa[fy] = fx;
	}
	int cnt = 0;
	up(i,1,n) if(fa[i]==i) cnt++;
	return cnt <= k;
}
double l,r;
inline bool cmp(edge a,edge b){return a.dis < b.dis;}
inline void prework()
{
	l = 1e20,r = -1e20;
	io >> k >> n;
	up(i,1,n) io >> p[i].x >> p[i].y;
	up(i,1,n) up(j,i+1,n)
	{
		double dis = sqrt((p[i].x-p[j].x) * (p[i].x-p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
		e[++tot] = (edge){i,j,dis};
		l = min(l,dis), r = max(r,dis);
	}
	sort(e+1,e+tot+1,cmp);
}
int main()
{
	prework();
	if(tot==1){printf("%.2lf",e[1].dis);return 0;}
	double ans = 0;
	while(l < r-eps)
	{
		double mid = (l+r)/2;
		if(check(mid)) r = mid,ans = mid;
		else l = mid;
	}
	printf("%.2lf",ans);
	return 0;
}
