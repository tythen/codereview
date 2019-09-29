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
inline void make()
{
	flag[1] = 1;
	for(int i=2;i<=1e6;i++)
	{
		if(!flag[i]) prime[++cnt] = i;
		for(int j=1;j<=cnt && prime[j]*i<=1e6;j++)
		{
			flag[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
}
int n;
int main()
{
	make();
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0) return 0;
		int t = 0;
		for(int i=1;i<=cnt;i++)
		{
			if((n-prime[i])%2 && !flag[n-prime[i]])
			{
				printf("%lld = %d + %d\n",n,prime[i],n-prime[i]);
				t=1;
				break;
			}
		}
		if(!t) puts("Goldbach's conjecture is wrong.");
	}

}
