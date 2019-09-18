#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		re int f=1;x=0;re char c=getchar();
		for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
		for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
		x*=f;
		return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char c) {putchar(c);return *this;}
}io;
/*
m个数放入n个格子 问多少种方案会有相同的数相邻 
用总数来减的方法
n个格子m个数共m^n
考虑不相邻的情况：第一个人有m种情况，剩下n-1个人，为了不与左边相同，有m-1种方案
不相邻一共m* (m-1)^(n-1)
ans = m^n - m* (m-1)^(n-1) 
*/
const int mod = 100003;
inline ll ksm(ll a,ll b,ll mod){
	ll ans=1;
	for(;b;b>>=1,a=(a*a)%mod) if(b&1) ans = (ans*a)%mod;
	return ans;
}
ll n,m;
int main()
{
	io >> m >> n; 
	if(n==1){
		puts("0");
		return 0; 
	}
	io << (ksm(m,n,mod) - m*ksm((m-1),n-1,mod)%mod + mod)%mod;
}
