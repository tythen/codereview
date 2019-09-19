#include<bits/stdc++.h>

#define re register
#define ll long long
#define isa(c) (c>='0'&&c<='9')

using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		x=0;int f=1;register char c=getchar();
		for(;!isa(c);c=getchar()) if(c=='-') f=-1;
		for(;isa(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) *this << x/10;
		putchar(x%10+48);
	}
	inline ios& operator << (char x){putchar(x);}
}io;
const int N = 300;
ll dp_max[N][N],dp_min[N][N];
int n,a[N],sum[N];
int main()
{
	io >> n;
	for(int i=1;i<=n;i++) io >> a[i],a[i+n] = a[i];
	n *= 2;
	for(int i=1;i<=n;i++) sum[i] = sum[i-1] + a[i];
//	for(int i=1;i<=n;i++) dp_max[i][i] = dp_min[i][i] = a[i];这里在合并时会加入权值的，所以这里不用置初值 
	for(int len = 2;len <= n;len++)
	{
		for(int i = 1;i <= n;i++)
		{
			int j = i+len-1;
			if(j>n) continue;
			dp_min[i][j] = 0x7f7f7f7f;
			for(int k = i;k < j;k++)
			{
				dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j] + sum[j] - sum[i-1]);
				dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k+1][j] + sum[j] - sum[i-1]);
			}
		}
	}
	ll ans_max = 0,ans_min = 9999999999999;
	n /= 2;
	for(int i=1;i<=n;i++)  
		ans_max = max(ans_max,dp_max[i][i+n-1]),
		ans_min = min(ans_min,dp_min[i][i+n-1]);
	io << ans_min << '\n' << ans_max;
	return 0;
}
