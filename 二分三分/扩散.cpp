#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define ll long long
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=b;i>=a;--i)
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
const int N = 2e6+5;
/*
联通：2*t >= 曼哈顿距离 
二分时间，尽量最早
下界是最近的曼哈顿距离，上届是最远的曼哈顿距离 
*/
struct node{
	int a,b;
}points[60];
int n;
inline bool iscon(node i,node j,int t){
	return abs(i.a-j.a)+abs(i.b-j.b) <= 2*t;
}
int fa[N];
inline int find(int x){
	return x==fa[x] ? x:fa[x] = find(fa[x]);
}
inline bool check(int t)
{
	up(i,1,n) fa[i] = i;
	int cnt = 0;
	up(i,1,n) up(j,i+1,n)
	{
		int fx = find(i);
		int fy = find(j);
		if(fx==fy) continue;
		if(iscon(points[i],points[j],t)) fa[fy] = fx,cnt++;
	}
	return cnt==n-1;
}
int main()
{
	io >> n;
	up(i,1,n) io >> points[i].a >> points[i].b;
	int l = 0x7f7f7f7f,r = 0,ans = 0x7f7f7f7f;
	up(i,1,n) up(j,i+1,n)
	{
		int mhdis = abs(points[i].a-points[j].a)+abs(points[i].b-points[j].b);
		int cardis = min(abs(points[i].a-points[j].a),abs(points[i].b-points[j].b));
		l = min(l,cardis),r = max(r,mhdis);
	}
	while(l<=r)
	{
		int mid = l+r>>1;
		if(check(mid)) ans = mid,r = mid-1;
		else l = mid+1;
	}
	io << ans;
	return 0;
}
