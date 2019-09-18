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
m��������n������ �ʶ����ַ���������ͬ�������� 
�����������ķ���
n������m������m^n
���ǲ����ڵ��������һ������m�������ʣ��n-1���ˣ�Ϊ�˲��������ͬ����m-1�ַ���
������һ��m* (m-1)^(n-1)
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
