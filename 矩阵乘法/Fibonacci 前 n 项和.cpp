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
const int N = 1e6+5;
const int inf = 0x7f7f7f7f;
ll mod; 
struct martix{
	int n,m;
	ll s[105][105];
	inline martix operator * (const martix b){
		martix c;
		c.n = n,c.m = b.m;
		for(int i=1;i<=c.n;i++) for(int j=1;j<=c.m;j++) c.s[i][j] = 0;
		for(int i=1;i<=c.n;i++) for(int j=1;j<=c.m;j++) for(int k=1;k<=m;k++) c.s[i][j] = (c.s[i][j] + (s[i][k] * b.s[k][j])%mod)%mod;
		return c;
	}
	inline void print(){
		for(int i=1;i<=n;i++,puts("")) for(int j=1;j<=m;j++) io <<s[i][j] <<' ';
	}
}f,M;
int n;
int main(){
	io >> n >> mod;
	f.n = 3,f.m = 1;M.n = M.m = 3;
	f.s[1][1] = f.s[3][1] = 1;
	M.s[1][1] = M.s[1][2] = M.s[1][3] = M.s[2][3] = M.s[3][2] = M.s[3][3] = 1;
	n--;
	for(;n;n>>=1,M = M * M) if(n&1) f = M * f;
	io << f.s[1][1];
	return 0;
}
