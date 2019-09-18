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
struct martix{
	int n,m;
	int s[105][105];
	inline void set(int x,int y,int val){s[x][y] = val;}
	inline martix operator *= (const martix b){
		martix c;
		c.n = n,c.m = b.m;
		memset(c.s,0,sizeof c.s);
		for(int i=1;i<=c.n;i++)
			for(int j=1;j<=c.m;j++)
				for(int k=1;k<=m;k++)
					c.s[i][j] += s[i][k] * b.s[k][j];
		return c;
	}
	inline void print(){
		for(int i=1;i<=n;i++,puts(""))
			for(int j=1;j<=m;j++)
				io << s[i][j] << ' ';
	}
}A,B;
int main(){
	io >> A.n >> A.m;
	for(int i=1;i<=A.n;i++)
		for(int j=1;j<=A.m;j++)
			io >> A.s[i][j];
	io >> B.m;B.n = A.m;
	for(int i=1;i<=B.n;i++)
		for(int j=1;j<=B.m;j++)
			io >> B.s[i][j];
	(A*=B).print();
	return 0;
}
