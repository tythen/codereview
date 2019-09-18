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
const int N = 1e5+6;
const int inf = 0x7f7f7f7f;
ll a[N],p;
int n,m;
struct segment{
	ll sum[N<<2],len[N<<2],add[N<<2],mul[N<<2];
	#define ls rt<<1
	#define rs rt<<1|1
	#define mid (l+r>>1)
	inline void pushup(int rt){sum[rt] = (sum[ls] + sum[rs])%p; } 
	inline void spadd(int rt,ll val)
	{
		add[rt] = (add[rt] + val) % p;
		sum[rt] = (sum[rt] + val*len[rt]) % p;	
	}
	inline void spmul(int rt,ll val)
	{
		mul[rt] = (mul[rt] * val) % p;
		add[rt] = (add[rt] * val) % p;
		sum[rt] = (sum[rt] * val) % p;		
	}
	inline void pushdown(int rt)
	{
		spmul(ls,mul[rt]);
		spmul(rs,mul[rt]);
		mul[rt] = 1;
		spadd(ls,add[rt]);
		spadd(rs,add[rt]);
		add[rt] = 0;
	}
	inline void build(int rt,int l,int r)
	{
		len[rt] = r-l+1;
		add[rt]=0;mul[rt]=1;
		if(l==r){sum[rt]=a[l];return;}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int L,int R,ll val,int Tag)
	{
		if(L <= l && r <= R)
		{
			if(Tag==1) spmul(rt,val);
			else spadd(rt,val);
			return;
		}
		pushdown(rt);
		if(L<=mid) modify(ls,l,mid,L,R,val,Tag);
		if(R> mid) modify(rs,mid+1,r,L,R,val,Tag);
		pushup(rt);
	}
	inline ll query(int rt,int l,int r,int L,int R)
	{
		ll ret = 0;
		if(L <= l && r <= R) return sum[rt];
		pushdown(rt);
		if(L<=mid) ret = (ret + query(ls,l,mid,L,R)) % p;
		if(R> mid) ret = (ret + query(rs,mid+1,r,L,R)) % p;
		pushup(rt);	
		return ret;	
	}
}T;
int x,l,r,c;
int main()
{
	io >> n >> p;
//	io >> n >> m >> p;
	for(int i=1;i<=n;i++) io >> a[i];
	T.build(1,1,n);
//	printf("a[]=");for(int i=1;i<=n;i++) io << T.query(1,1,n,i,i) << ' ';puts("");
	io >> m;
	while(m--)
	{
		io >> x >> l >> r;
		if(x==1||x==2) 
		{
			io >> c;
			T.modify(1,1,n,l,r,c,x);
		}
		else io << T.query(1,1,n,l,r) << '\n';
//		printf("a[]=");for(int i=1;i<=n;i++) io << T.query(1,1,n,i,i) << ' ';puts("");
	}
	return 0;
}
