#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
#define re register

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
/*
区间覆盖问题 
按开始位置排序 
在覆盖了当前端点的区间中选右端点最靠右的一个就可以了 
*/ 
const int N = 3e5+5;
const double eps = 1e-6;
int n,m;

struct node{
	double l,r;
}a[N];
int vis[N];
inline bool cmp(node x,node y){
	return x.l < y.l;
}
int L,W,T;
int pos,r;
int main(){
	io >> T;
	while(T--){
		io >> n >> L >> W;
		int cnt = 0;
		for(int i=1;i<=n;i++){
			io >> pos >> r;
			if(r+r < W) continue;//因为有完全没用的点，所以要记cnt 
			double d = sqrt(r*r - (W*W/4.0));
			a[++cnt].l = 1.0*pos - d;
			a[cnt].r = 1.0*pos + d;
		}
		sort(a+1,a+1+cnt,cmp);
		int ans = 0;
		int now = 0;
		while(a[now].r < L || fabs(a[now].r-L) < eps){
			int go = now;
			for(int i=now+1;i<=cnt;i++){
				if((a[i].l < a[now].r||fabs(a[i].l-a[now].r < eps)) && a[i].r > a[go].r){
					go = i;
				}
				if(a[i].l > a[now].r) break;
			}
			if(go==now) {
				ans = -1;
				break;
			}
			now = go;
			ans++;
		}
		io << ans << '\n';
	}
	return 0;
} 
