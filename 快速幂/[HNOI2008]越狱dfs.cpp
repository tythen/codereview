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
*/
const int mod = 100003;
int n,m;
int ans;
int a[1000];
inline void dfs(int pos,int flag,int last){
	if(pos==n+1) {
		if(flag)ans++;
//		for(int i=1;i<=n;i++) io << a[i] << ' ';io << flag;puts("");
		return ;
	}
	for(int i=1;i<=m;i++){
		a[pos] = i;
		if(i==last) dfs(pos+1,flag|1,i);
		else dfs(pos+1,flag|0,i);
	}
}
inline ll ksm(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=(a*a)%mod) if(b&1) ans = (ans*a)%mod;
	return ans;
}
int main()
{
	for(m=1;m<=6;m++)
	for(n=1;n<=6;n++)
	{
		printf("%d %d:",m,n);
		ans =0 ;
		dfs(1,0,0);
		io << ans%mod << '\n';
//		io << ksm(m,n) << ' '<<ksm(m,n) - ans <<'\n';		
	}

}
