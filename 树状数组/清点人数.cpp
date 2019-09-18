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
int n,m,k,p; 
struct bit_tree{
	int c[N];
	inline void add(int x,ll val)
	{
		for(re int i=x;i<=n;i += -i&i) c[i] += val;//最大的写错了啊 
	}
	inline ll query(int x)
	{
		ll ret = 0;
		for(re int i=x;i;i -= -i&i) ret += c[i];
		return ret;
	}
}T;
char ins[3]; 
int main()
{
	io >> n >> k;
	for(re int i=1;i<=k;i++)
	{
		scanf("%s",ins);
		if(ins[0]=='A')
		{
			io >> m;
			io << T.query(m) << '\n';
		}
		else if(ins[0]=='B')
		{
			io >> m >> p;
			T.add(m,p);
		}
		else
		{
			io >> m >> p;
			T.add(m,-p);			
		}
	}
}
