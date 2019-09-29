#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<limits>

#define ll long long
#define ull unsigned ll
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=a;i>=b;--i)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
#define cmax(a,b) a = max(a,c)
#define cmin(a,b) a = min(a,b)
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
const int inf = numeric_limits<int>::max()-10;
const int N = 2000005;
ll prime[N],cnt,flag[N];
inline void make()
{
	flag[1] = 1;
	for(int i=2;i<=N;i++)
	{
		if(!flag[i]) prime[++cnt] = i;
		for(int j=1;j<=cnt && i*prime[j]<=N;j++)
		{
			flag[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
		}
	}
}
ll L,R;
ll he[2000000];
int main()
{
	make();
	while(scanf("%d%d",&L,&R)!=EOF)
	{
		for(ll i=L;i<=R;i++) he[i - L] = 0;
		for(ll i=1;prime[i]*prime[i]<=R;i++)
		{
			for(int j=L/prime[i];j*prime[i]<=R;j++)//直接L/prime[j]让它直接靠近区间 
			{
				if(j*prime[i] < L || j==1) continue;//j为1的话会把本身是质数的数筛成合数 
				he[j*prime[i] - L] = 1;
			}
		}
		int last = 0;
		int mindis = inf,maxdis = -inf;
		if(L<=1) he[1-L] = 1;//特判：1是合数 
		pair<int,int> ans1,ans2;
		for(ll i=L;i<=R;i++) 
		{
			if(!he[i - L])
			{
				if(!last) last = i;
				else 
				{
					if(maxdis < i-last)
					{
						maxdis = i-last;
						ans2.first = last,ans2.second = i;
					}
					if(mindis > i-last)
					{
						mindis = i-last;
						ans1.first = last,ans1.second = i;
					}
					last = i;
				}
			}
		}
		if(mindis==inf) puts("There are no adjacent primes.");
		else printf("%d,%d are closest, %d,%d are most distant.\n",ans1.first,ans1.second,ans2.first,ans2.second);
		
	}
	return 0;
}
