#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define re register
#define ls rt<<1
#define rs rt<<1|1
#define mid (l+r>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
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
const int N = 3e4+5;
/*
树链剖分的组成
找重儿子 拉重链 支持区间和区间最值的线段树 跳链查询的函数
*/
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
ll w[N],wt[N],n;
struct segment_tree{
	ll sum[N<<2],Max[N<<2];
	inline void pushup(int rt){sum[rt] = sum[ls]+sum[rs];Max[rt] = max(Max[ls],Max[rs]); }
	inline void build(int rt,int l,int r)
	{
		if(l==r){sum[rt]=Max[rt]=wt[l];return; }
		build(lson),build(rson);
		pushup(rt);
	}
	inline ll query_sum(int rt,int l,int r,int L,int R)
	{
		if(L <= l && r <= R) return sum[rt];
		ll ret = 0;
		if(L<=mid) ret += query_sum(lson,L,R);
		if(R >mid) ret += query_sum(rson,L,R);
		return ret;
	}
	inline ll query_max(int rt,int l,int r,int L,int R)
	{
		if(L <= l && r <= R) return Max[rt];
		ll ret = -99999999999999;
		if(L<=mid) ret = max(ret,query_max(lson,L,R));
		if(R >mid) ret = max(ret,query_max(rson,L,R));
		return ret;
	}
	inline void modify(int rt,int l,int r,int pos,ll val)
	{
		if(l==r) 
		{
			sum[rt] = Max[rt] = val;
			return;
		}
		if(pos<=mid) modify(lson,pos,val);
		else modify(rson,pos,val);
		pushup(rt);
	}
}seg;
struct treechain{
	int size[N],hson[N],fa[N],top[N],id[N],idx,dep[N];
	inline void dfs1(int x,int f)
	{
		size[x] = 1;
		fa[x] = f;dep[x] = dep[f]+1;
		for(int i=h[x];i;i=e[i].nxt)
		{
			int v = e[i].v; 
			if(v==f) continue;
			dfs1(v,x);
			size[x] += size[v];
			if(!hson[x] || size[v]>size[hson[x]]) hson[x] = v;
		}
	}
	inline void dfs2(int x,int topx)
	{
		id[x] = ++idx;
		wt[idx] = w[x];
		top[x] = topx;
		if(size[x]==1) return;
		dfs2(hson[x],topx);
		for(int i=h[x];i;i=e[i].nxt)
		{
			int v = e[i].v;
			if(v==fa[x] || v==hson[x]) continue;
			dfs2(v,v);
		}
	}
	inline ll Qmax(int x,int y)
	{
		ll ret = -999999999999;
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			ret = max(ret,seg.query_max(1,1,n,id[top[x]],id[x]));
			x = fa[top[x]];
 		}
		if(dep[x]>dep[y]) swap(x,y);
		ret = max(ret,seg.query_max(1,1,n,id[x],id[y]));
		return ret;
	}
	inline ll Qsum(int x,int y)
	{
		ll ret = 0;
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			ret += seg.query_sum(1,1,n,id[top[x]],id[x]);
			x = fa[top[x]];
		}
		if(dep[x] > dep[y]) swap(x,y);
		ret += seg.query_sum(1,1,n,id[x],id[y]);
		return ret;
	}
	inline void build()
	{
		dfs1(1,0);
		dfs2(1,0);
		seg.build(1,1,n);
	}
}T;
char ins[10];
ll a,b,q;

int main()
{
	io >> n;
	for(int i=1;i<n;i++) io >> a >> b,add(a,b),add(b,a);
	for(int i=1;i<=n;i++) io >> w[i];
	T.build();
	io >> q;
	while(q--)
	{
		scanf("%s",ins);
		io >> a >> b;
		if(ins[1]=='M') io << T.Qmax(a,b) << '\n';
		else if(ins[1]=='S') io << T.Qsum(a,b) << '\n';			
		else seg.modify(1,1,n,T.id[a],b);
//		printf("wt[]=");for(int i=1;i<=n;i++) io << seg.query_sum(1,1,n,i,i) << ' ';puts("");
	}
	return 0;
}
