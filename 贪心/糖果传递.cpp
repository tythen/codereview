#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
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
const int N = 1e6+5;
const int inf = 0x7f7f7f7f;

int n;
ll a[N],sum[N];
ll tot,ave,ans;
int main(){
	io >> n;
	for(int i=1;i<=n;i++) io >> a[i],tot += a[i];
	ave = tot / n;
	for(int i=1;i<=n;i++){
		a[i] -= ave;
		sum[i] = sum[i-1] + a[i];
	}
	sort(sum+1,sum+1+n);
	int mid = (1+n)>>1;
	for(int i=1;i<=n;i++){
		ans += abs(sum[i] - sum[mid]);
	}
	io << ans;
	return 0;
}
