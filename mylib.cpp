#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long 
#define re register

#define up(i,a,b) for(register int i=a;i<=b;i++) 
#define down(i,a,b) for(register int i=a;i>=b;i--) 
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
/*
ty的STL库：已包含 
st表，矩阵，邻接矩阵，线段树，树链剖分 ，树状数组，hash表 
*/
int N = 1e6+5;
const int mod = 1e9+7;
struct st_list{
	ll st_max[20][N],st_min[20][N];
	int lg[N];
	inline void build(int n){
		lg[0] = -1;
		for(register int i=1;i<=n;i++) st_max[0][i] = st_min[0][i] = a[i],lg[i] = lg[i>>1] + 1;
		for(register int i=1;i<=lg[n];i++)
			for(register int j=1;j<=n;j++)
				st_max[i][j] = max(st_max[i-1][j], st_max[i-1][j+(1<<(i-1))]),
				st_min[i][j] = min(st_min[i-1][j], st_min[i-1][j+(1<<(i-1))]);
	}
	inline ll query_max(int l,int r){
		int k = lg[r-l+1];
		return max(st_max[k][l], st_max[k][r-(1<<k)+1]);
	}
	inline ll query_min(int l,int r){
		int k = lg[r-l+1];
		return min(st_min[k][l], st_min[k][r-(1<<k)+1]);
	}	
};
struct martix{
	int n,m;
	ll s[105][105];
	inline martix operator * (const martix b){
		martix c;
		c.n = n,c.m = b.m;
		for(int i=1;i<=c.n;i++) for(int j=1;j<=c.m;j++) c.s[i][j] = 0;
		for(int i=1;i<=c.n;i++)
			for(int j=1;j<=c.m;j++)
				for(int k=1;k<=m;k++)
					c.s[i][j] = (c.s[i][j] + (s[i][k]*b.s[k][j])%mod)%mod;
		return c;
	}
	inline void print(){
		for(int i=1;i<=n;i++,puts("")) for(int j=1;j<=m;j++) io << s[i][j] << ' ';
	}
};

struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add_edge(int x,int y){
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
};

struct bit_tree{
	ll c[N];
	inline void add(int pos,ll val){
		for(int i=pos;i<=n;i += -i&i) c[i] += val;
	}
	inline ll query(int pos){
		ll ret = 0;
		for(int i=pos;i;i -= -i&i) ret += c[i];
		return ret;
	}
};

struct hash_table{
	struct node{int key;int val,nxt;}e[N];
	int h[N],tot;
	inline int& operator [] (const int key)
	{
		for(int i=h[key%p];i;i=e[i].nxt) if(e[i].key == key) return e[i].val;
		e[++tot] = (node){key,0,h[key%p]};
		h[key%p] = tot;
		return e[tot].val;
	}
	inline void clear()
	{
		for(int i=0;i<=tot;i++) h[i] = 0,e[i].key = e[i].nxt = e[i].val = 0;
		tot = 0;
	}
};

