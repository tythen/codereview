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
const int N = 1e6+6;
const int inf = 0x7f7f7f7f;
ll a[N];
struct segment_tree{
	ll Max[N<<2];
	#define ls rt<<1
	#define rs rt<<1|1
	#define mid (l+r>>1)
	#define len (r-l+1)
	#define lenls (mid-l+1)
	#define lenrs (r-mid)
	inline void pushup(int rt) {Max[rt] = max(Max[ls],Max[rs]);}

	inline void build(int rt,int l,int r)
	{
		if(l==r){Max[rt] = 0;return;}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int pos,ll val)
	{
		if(l==r && l==pos)
		{
			Max[rt] = val;
			return;
		}
		if(pos <= mid) modify(ls,l,mid,pos,val);
		if(pos >  mid) modify(rs,mid+1,r,pos,val);
		pushup(rt);
	}
	inline ll query(int rt,int l,int r,int L,int R)
	{
		if(L <= l && r <= R) return Max[rt];
		ll ret = 0;
		if(L<=mid) ret = max(ret, query(ls,l,mid,L,R));
		if(R> mid) ret = max(ret, query(rs,mid+1,r,L,R));
		pushup(rt);
		return ret;
	}
}T;
int n,q,p;
int x,y,z;
ll A;
char ins[3];
int main()
{
	io >> q >> p;
	T.build(1,1,2e5);
	while(q--)
	{
		scanf("%s",ins);
		io >> x;
		if(ins[0]=='A')
		{
			++n;
			T.modify(1,1,2e5,n,(x+A)%p);
		}
		else io << (A = T.query(1,1,2e5,n-x+1,n)) <<'\n';
	}
	return 0;
}
