#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define ll long long
#define re register
#define rint register int
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
const int N = 2e5+6;
const int inf = 0x7f7f7f7f;
ll like[N];
/*
整数开方最多5次成1 
不对全是1的区间开方 
5 n logn  + m logn
*/
int n,m;
struct segment{
	ll sum[N<<2],Max[N<<2];
	#define ls rt<<1
	#define rs rt<<1|1
	#define mid ((l+r)>>1)
	inline void pushup(int rt){
		sum[rt] = sum[ls] + sum[rs]; 
		Max[rt] = max(Max[ls],Max[rs]);
	} 
	inline void build(int rt,int l,int r)
	{
		if(l==r){sum[rt] = Max[rt] = like[l];return;}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int L,int R)
	{
		if(l==r){
			sum[rt] = floor(sqrt(sum[rt])); 
			Max[rt] = floor(sqrt(Max[rt])); 
			return;
		}
		if(Max[ls]>1 && L<=mid) modify(ls,l,mid,L,R);
		if(Max[rs]>1 && R> mid) modify(rs,mid+1,r,L,R);
		pushup(rt);
	}
	inline ll query(int rt,int l,int r,int L,int R)
	{
		ll ret = 0;
		if(L <= l && r <= R) return sum[rt];
		if(L<=mid) ret += query(ls,l,mid,L,R);
		if(R> mid) ret += query(rs,mid+1,r,L,R);
		return ret;
	}
}T;
ll x,l,r;
int main()
{
	io >> n;
	for(int i=1;i<=n;i++) io >> like[i];
	T.build(1,1,n);
	io >> m;
	while(m--)
	{
		io >> x >> l >> r;
		if(r<l) swap(l,r);
		if(x==1) io << T.query(1,1,n,l,r) << '\n';
		else T.modify(1,1,n,l,r);
	}
	return 0;
}
