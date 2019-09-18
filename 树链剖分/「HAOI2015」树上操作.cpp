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
#define len (r-l+1)
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
const int N = 1e5+5;
int n;
struct edge{
	int v,nxt;
}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
ll wt[N],w[N];
struct segment{
	ll sum[N<<2],add[N<<2];
	inline void pushup(int rt){
		sum[rt] = sum[ls] + sum[rs];
	}
	inline void spread(int rt,int l,int r,ll val){
		sum[rt] += val*len;
		add[rt] += val;		
	}
	inline void pushdown(int rt,int l,int r){
		spread(ls,l,mid,add[rt]);
		spread(rs,mid+1,r,add[rt]);
		add[rt] = 0;
	}
	inline void build(int rt,int l,int r){
		if(l==r){sum[rt]=wt[l]; return;}
		build(lson),build(rson);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int L,int R,ll val){
		if(L<=l && r<=R){
			spread(rt,l,r,val);
			return;
		}
		pushdown(rt,l,r);
		if(L<=mid) modify(lson,L,R,val);
		if(R> mid) modify(rson,L,R,val);
		pushup(rt);
	}
	inline ll query(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R){return sum[rt];}
		ll ret = 0;
		pushdown(rt,l,r);
		if(L<=mid) ret += query(lson,L,R);
		if(R> mid) ret += query(rson,L,R);
		return ret;
	}
}seg;
struct treechain{
	int dep[N],fa[N],top[N],hson[N],size[N],id[N],idx;
	inline void dfs1(int x,int f){
		fa[x] = f;dep[x] = dep[f] + 1;
		size[x] = 1;
		for(int i=h[x];i;i=e[i].nxt){
			int v = e[i].v;
			if(v==f) continue;
			dfs1(v,x);
			size[x] += size[v];
			if(!hson[x] || size[v]>size[hson[x]]) hson[x] = v;
		}
	}
	inline void dfs2(int x,int topx){
		id[x] = ++idx;
		wt[idx] = w[x];top[x] = topx;
		if(!hson[x]) return;
		dfs2(hson[x],topx);
		for(int i=h[x];i;i=e[i].nxt){
			int v = e[i].v;
			if(v==fa[x] || v==hson[x]) continue;
			dfs2(v,v);
		}
	}
	inline ll Qsum(int x,int y){
		ll ret = 0;
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			ret += seg.query(1,1,n,id[top[x]],id[x]);
			x = fa[top[x]];
		}
		if(dep[x] > dep[y]) swap(x,y);
		ret += seg.query(1,1,n,id[x],id[y]);
		return ret;
	}
	inline void build(){
		dfs1(1,0);dfs2(1,0);seg.build(1,1,n);
	}
}T;
int m,a,b,ins;

int main()
{
	io >> n >> m;
	for(int i=1;i<=n;i++) io >> w[i];
	for(int i=1;i<n;i++){
		io >> a >> b;
		add(a,b),add(b,a);
	}
	T.build();
	while(m--){
		io >> ins >> a;
		if(ins==1){
			io >> b;
			seg.modify(1,1,n,T.id[a],T.id[a],b);
		}
		else if(ins==2){
			io >> b;
			seg.modify(1,1,n,T.id[a],T.id[a]+T.size[a]-1,b);
		}
		else io << (T.Qsum(1,a)) << '\n';
	}
}
