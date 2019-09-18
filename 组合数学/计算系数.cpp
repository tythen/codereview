#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define re register
#define isa(c) (c>='0'&&c<='9')
using namespace std;
inline int read(){
	int x=0,f=1;register char c=getchar();
	for(;!isa(c);c=getchar()) if(c=='-') f=-1;
	for(;isa(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*=f;
}
const int N = 1e6+5;
const int mod = 10007;
/*
二项式定理：
ans = C(k,n)*a^n*b^(k-n) 
*/
ll jc[N<<1],inv[N<<1];
inline ll C(ll n,ll m)
{
	return jc[n] * inv[m] %mod * inv[n-m] %mod; 
}

inline ll ksm(ll a,ll b)
{
	ll ans = 1;
	for(;b;b>>=1,a=(a*a)%mod) if(b&1) ans = (ans * a) % mod;
	return ans;
}

int n,m,a,b,k;
int main()
{
	jc[0] = 1;
	for(int i=1;i<=mod;i++)  
		jc[i] = (jc[i-1] * i) % mod;
	inv[mod-1] = ksm(jc[mod-1],mod-2);
	for(int i=mod-2;i>=1;i--) inv[i] = (inv[i+1] * (i+1)%mod)%mod;
	a = read(), b = read(), k = read(), n = read(), m = read();
	printf("%d",C(k,n) * ksm(a,n) %mod * ksm(b,m) % mod);
	return 0;
}
