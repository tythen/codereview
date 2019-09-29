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
#define cmax(a,b) a = max(a,b)
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
const ll inf = numeric_limits<ll>::max()-10;
const int N = 2000005;
/*
求对于序列中每一个数有多少数可以整除它 
*/
ll n;
ll arr[N],b[N];
int flag[N];
ll maxx = -inf;
int main()
{
	io >> n;
	up(i,1,n) 
	{
		io >> arr[i];
		b[i] = arr[i];
		flag[b[i]]++;
		cmax(maxx,b[i]);
	}
	for(int i=1;i<=n;i++)//对每一个数用试除法 
	{
		int ans = 0;
		for(int j=1;j*j<=b[i];j++)
		{
			if(b[i]%j==0)
			{
				ans += flag[j];
				if(b[i]/j!=j) ans += flag[b[i]/j];
			}
		}
		io << ans-1 << '\n';
	}
}
