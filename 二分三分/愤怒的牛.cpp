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
const int N = 2e5+5;
int x[N],n,m;
inline bool check(int d)
{
	int cnt = 1,nowdis = x[1]+d;
	up(i,2,n){
		if(x[i] < nowdis) continue;
		cnt++;
		nowdis = x[i] + d;
	}
	return cnt>=m;
}
int main()
{
	io >> n >> m;
	int l,r;
	up(i,1,n) io >> x[i];
	sort(x+1,x+1+n);
	l = 1,r = x[n];
	int ans = 0;
	while(l<=r)
	{
		int mid = l+r >> 1;
		if(check(mid)) ans = mid,l = mid+1;
		else r = mid-1;
	}
	io << ans;//最大化最小值 
	return 0;
}
