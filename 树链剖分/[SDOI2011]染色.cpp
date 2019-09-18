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
#define mid ((l(rt)+r(rt))>>1)
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
struct node{
	int l,r,lc,rc,tag;
	ll ans;
	#define l(x) t[x].l
	#define r(x) t[x].r
	node(){l=r=lc=rc=ans = 0;}
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define ans(x) t[x].ans
	#define tag(x) t[x].tag
}t[N<<2];
struct segment{
	inline void pushup(int rt){
		ans(rt) = ans(ls) + ans(rs);
		if(rc(ls) == lc(rs)) ans(rt)--;
		lc(rt) = lc(ls),rc(rt) = rc(rs);
	}
	inline void spread(int rt,int color){
		lc(rt) = rc(rt) = color;
		ans(rt) = 1;
		tag(rt) = color;
	}
	inline void pushdown(int rt){
		if(tag(rt)==-1) return;
		spread(ls,tag(rt)),spread(rs,tag(rt));
		tag(rt) = -1;
	}
	inline void build(int rt,int l,int r){
		l(rt) = l,r(rt) = r;tag(rt) = -1;
		if(l==r){lc(rt) = rc(rt) = wt[l],ans(rt) = 1;return;}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	inline void modify(int rt,int L,int R,ll val){//?lr???val 
		if(L<=l(rt) && r(rt)<=R){
			spread(rt,val);
			return;
		}
		pushdown(rt);
		if(L<=mid) modify(ls,L,R,val);
		if(R> mid) modify(rs,L,R,val);
		pushup(rt);
	}
	inline node query(int rt,int L,int R){
		if(L<=l(rt) && r(rt)<=R){return t[rt];}
		node ret,tl,tr;
		pushdown(rt);
		if(L<=mid && R<=mid) return query(ls,L,R);
		if(L> mid && R> mid) return query(rs,L,R);
		tl = query(ls,L,R),tr = query(rs,L,R);
		ret.ans = tl.ans + tr.ans;
		if(tl.rc == tr.lc) ret.ans--;
		ret.lc = tl.lc,ret.rc = tr.rc;		
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
	inline ll Qans(int x,int y){
		ll ret = 0;
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			ret += seg.query(1,id[top[x]],id[x]).ans;
			if(seg.query(1,id[fa[top[x]]],id[fa[top[x]]]).lc == seg.query(1,id[top[x]],id[top[x]]).lc) ret--;//在跳链的时候可能会出现颜色合并的情况 
			x = fa[top[x]];
		}
		if(dep[x] > dep[y]) swap(x,y);
		ret += seg.query(1,id[x],id[y]).ans;
		return ret;
	}
//	inline ll Qans(int x,int y){书上的写法，现在看不懂 
//		ll ret = 0;
//		int lastx=-1,lasty=-1;
//		while(top[x] != top[y]){
//			if(dep[top[x]] < dep[top[y]]) swap(x,y),swap(lastx,lasty);
//			node q = seg.query(1,id[top[x]],id[x]);
//			ret += q.ans;
//			if(lastx == q.rc) ret--;
//			lastx = q.lc;
//			x = fa[top[x]];
//		}
//		if(dep[x] > dep[y]) swap(x,y),swap(lastx,lasty);
//		node q = seg.query(1,id[x],id[y]);
//		ret += q.ans;
//		if(lastx == q.lc) ret--;
//		if(lasty == q.rc) ret--;
//		return ret;
//	}
	inline void change(int x,int y,int c){
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			seg.modify(1,id[top[x]],id[x],c);
			x = fa[top[x]];
		}
		if(dep[x] > dep[y]) swap(x,y);
		seg.modify(1,id[x],id[y],c);
	}	
	inline void build(){
		dfs1(1,0);dfs2(1,0);seg.build(1,1,n);
	}
}T;
int m,a,b,c;
char ins[10];
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
		scanf("%s",ins);
		io >> a >> b;
		if(ins[0]=='C'){
			io >> c;
			T.change(a,b,c);
		}else{
			io << T.Qans(a,b) << '\n';
		}
	}
}
