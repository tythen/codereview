#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int N = 5000;
int n,m; 
struct bit_tree{
	ll c[N][N];
	inline void add(int x,int y,ll val)
	{
		for(int i=x;i<=n;i += -i&i) 
			for(int j=y;j<=m;j += -j&j)
				c[i][j] += val;
	}
	inline ll query(int x,int y)
	{
		ll ret = 0;
		for(int i=x;i;i -= -i&i)
			for(int j=y;j;j -= -j&j)
				ret += c[i][j];
		return ret;
	}
}T;

ll a,b,c,d;
int ins; 
int main()
{
	io >> n >> m;
	while(scanf("%d",&ins)!=EOF)
	{
		if(ins==1)
		{
			io >> a >> b >> c;
			T.add(a,b,c);
		}
		else
		{
			io >> a >> b >> c >> d;
			io << T.query(c,d) - T.query(c,b-1) - T.query(a-1,d) + T.query(a-1,b-1) << '\n';
		}
	}
}
