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
const int N = 1e5+5;//区间染色+子树size 
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
	ll sum[N<<2];
	int set[N<<2];
	inline void pushup(int rt){
		sum[rt] = sum[ls] + sum[rs];
	}
	inline void spread(int rt,int l,int r,int val){
		if(val==1) sum[rt] = 0;
		else if(val==2) sum[rt] = len;
		set[rt] = val;
	}
	inline void pushdown(int rt,int l,int r){
		if(set[rt]==0) return;
		spread(ls,l,mid,set[rt]);
		spread(rs,mid+1,r,set[rt]);
		set[rt] = 0;
	}
	inline void build(int rt,int l,int r){
		if(l==r){sum[rt]=wt[l]; return;}
		build(lson),build(rson);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int L,int R,int val){
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
	inline void set(int x,int y,int val){
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			seg.modify(1,1,n,id[top[x]],id[x],val);
			x = fa[top[x]];
		}
		if(dep[x] > dep[y]) swap(x,y);
		seg.modify(1,1,n,id[x],id[y],val);
	}	
	inline void build(){
		dfs1(1,0);dfs2(1,1);seg.build(1,1,n);
	}
}T;
int m,a,b;
char ins[20];
int main()
{
	io >> n;
	for(int i=2;i<=n;i++){
		io >> a;a++;
		add(i,a),add(a,i);
	}
	T.build();
	io >> m;
	while(m--){
		scanf("%s",ins); 
		io >> a;a++;
		if(ins[0]=='i'){
			io << T.dep[a] - T.Qsum(1,a) << '\n';
			T.set(1,a,1);//val = 1设置成0有区间覆盖0之后再覆盖1 
			T.set(1,a,2);//val = 2设置成1 
		}
		else{
			io << seg.query(1,1,n,T.id[a],T.id[a]+T.size[a]-1) << '\n';
			seg.modify(1,1,n,T.id[a],T.id[a]+T.size[a]-1,1);
		}
	}

}
