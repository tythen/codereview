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
int n,L,a[N],b[N];
ll sum[N],minn[N];//问题转化成一个序列求子序列可否平均数大于某值，可以先把所有值减去这个平均数 
inline bool check(int ave)
{
	up(i,1,n) b[i] = a[i]*1000-ave,minn[i] = 0x7f7f7f7f;
	sum[0] = 0;
	up(i,1,n) sum[i] = sum[i-1] + b[i],minn[i] = min(sum[i],minn[i-1]);
	ll maxx=-0x7f7f7f7f;
	up(i,1,n)
	{
		if(i<L) continue;
		maxx = max(maxx,sum[i] - minn[i-L]);
	}
	return maxx>=0;
}
int main()
{
	io >> n >> L;
	int l=0x7f7f7f7f,r=0;
	up(i,1,n) io >> a[i],l = min(l,a[i]),r = max(r,a[i]);
	int ans = 0;l*=1000,r*=1000;
	while(l <= r)
	{
		int mid = l+r>>1;
		if(check(mid)) ans=mid,l = mid+1;
		else r = mid-1; 
	}
	io << ans;
	return 0;
}
