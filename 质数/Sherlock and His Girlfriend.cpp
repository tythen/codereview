#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define ll long long
#define re register
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		x=0;int f=1;register char c = getchar();
		for(;!isdigit(c);c=getchar()) if(c=='-') f = -1;
		for(;isdigit(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
const int N = 2e6+5;
int prime[N],cnt,flag[N];
int col[N];
inline void make()
{
	flag[1] = 1;col[1] = 1;
	for(int i=2;i<=1e6;i++)
	{
		if(!flag[i]) prime[++cnt] = i,col[i] = 1;
		for(int j=1;j<=cnt && prime[j]*i<=1e6;j++)
		{
			flag[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
}
int n;
int ans = 1;//不初始化就是0分 
int main()
{
	make();
	io >> n;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=2;j*prime[i]<=n+1;j++)
		{
			col[j*prime[i]] = col[prime[i]]+1;
			ans = max(ans,col[j*prime[i]]);
		}
	}
	io << ans << '\n';
	up(i,2,n+1) io << col[i] << ' ';
}
