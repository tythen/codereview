#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
#define re register
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
const int N = 5e5;
int n,m; 
struct bit_tree{
	ll c[N];
	inline void add(int x,ll val)
	{
		for(int i=x;i<=n;i += -i&i) c[i] += val;
	}
	inline ll query(int x)
	{
		ll ret = 0;
		for(int i=x;i;i -= -i&i) ret += c[i];
		return ret;
	}
}T;
int ins,a,b; 
int main()
{
	io >> n >> m;
	while(m--)
	{
		io >> ins >> a;
		if(ins==1)
		{
			io >> b;
			T.add(a,1);
			T.add(b+1,-1);
		}
		else io << T.query(a)%2 << '\n';
//		printf("a[]=");for(int i=1;i<=n;i++) io << T.query(i)%2;puts("");
	}
}
