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
const int N = 1e5;
int n,mx; 
struct bit_tree{
	int c[N];
	inline void add(int x,ll val)
	{
		for(re int i=x;i<=mx;i += -i&i) c[i] += val;//最大的写错了啊 
	}
	inline ll query(int x)
	{
		ll ret = 0;
		for(re int i=x;i;i -= -i&i) ret += c[i];
		return ret;
	}
}T;
struct node{int x,y;}a[N];
int ans[N];
int main()
{
	io >> n;
	for(re int i=1;i<=n;i++) io >> a[i].x >> a[i].y,mx = max(mx,a[i].x+1);
	for(re int i=1;i<=n;i++)
	{
		a[i].x++,a[i].y++;//这种致命错误居然只卡一个点，感动人性 
		ans[T.query(a[i].x)]++;//他给的是按y排的实际上swap一下也行 
		T.add(a[i].x,1);
	}
	for(re int i=0;i<n;i++) io<<ans[i]<<'\n';
}
