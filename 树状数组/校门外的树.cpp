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
const int N = 2e5+5;
int n; 
/*
可以用线段树+区间修改+区间最大来处理
但是可以利用括号匹配的思想，转化成一种不那么偏数学的模型
求区间'('和')'的数量，若被夹一次算一种树
右端点查询左括号就知道有多少左括号套到右边，然后减左端点查询的右括号把所有的在外面的树匹配了就可以了 
*/
inline int lowbit(int x){return (-x)&x;}
struct bit_tree{
	int c[N];
	inline void add(int pos,int val)
	{
		for(int i=pos;i<=n+5;i += lowbit(i)) c[i] += val;
	}
	inline int query(int pos)
	{
		int ret = 0;
		for(int i=pos;i;i -= lowbit(i)) ret += c[i];
		return ret;
	} 
}L,R;
int m;
int ins,l,r;
int main()
{
	io >> n >> m;
	while(m--)
	{
		io >> ins >> l >> r;
		if(ins == 1) L.add(l,1),R.add(r,1);
		else io << L.query(r) - R.query(l-1) << '\n';
	}
	return 0;
}
