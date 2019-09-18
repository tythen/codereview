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
/*
    Tn = f1 + 2*f2 + 3*f3 + ... + n*fn;
设  Sn = f1 + f2 + f3 + ... + fn
	nSn= n*f1 + n*f2 + n*f3 + ... + n*fn
	Pn = nSn - Tn = (n-1)*f1 + (n-2)*f2 + (n-3)*f3 + ... + fn-1
	Pn+1 = (n+1)*Sn+1 - Tn+1 = (n)*f1 + (n-1)*f2 + (n-2)*f3 + ... + 2*fn-1 + fn
	Pn+1 = Pn + Sn+1
	Pn = Pn-1 + Sn
	Tn = nSn - Pn 
设计转移 fn = fn-1+fn-2, Sn = Sn-1+fn, Pn = Pn-1+Sn
最后计算Tn = nSn - Pn 
f1 = 1,fn-1 = 0,S1 = 1,T1 = 1,P1 = 0
*/
const int N = 1e6+5;
const int inf = 0x7f7f7f7f;
int mod;
struct martix{
	int n,m;
	ll s[105][105];
	inline martix operator * (const martix b){
		martix c;
		c.n = n,c.m = b.m;
		for(int i=1;i<=c.n;i++) for(int j=1;j<=c.m;j++) c.s[i][j] = 0;
		for(int i=1;i<=c.n;i++)
			for(int j=1;j<=c.m;j++)
				for(int k=1;k<=m;k++)
					c.s[i][j] = (c.s[i][j] + (s[i][k]*b.s[k][j])%mod)%mod;
		return c;
	}
	inline void print(){
		for(int i=1;i<=n;i++,puts("")) for(int j=1;j<=m;j++) io << s[i][j] << ' ';
	}
}f,M;
int n;
int main(){
	M.s[1][1] = M.s[1][2] = 1;
	M.s[2][2] = M.s[2][3] = 1;
	M.s[3][3] = M.s[3][4] = 1;
	M.s[4][3] = 1;
	f.s[2][1] = f.s[3][1] = f.s[4][1] = 1;//直接从f2开始递推 
	M.n = M.m = 4;
	f.n = 4,f.m = 1;
	
	io >> n >> mod;
	int tpn = n--;
	for(;n;n>>=1,M = M*M) if(n&1) f = M*f;
//	f.print();
	io << ((tpn*f.s[2][1])%mod - f.s[1][1] + mod)%mod;
	return 0;
}
