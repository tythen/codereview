#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
#define re register
#define mid ((l+r) >>1)

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
	���俪���߶���  ����ӣ��������ֵ  ���ɾ��
	ֹ�ޤ�ͤ������ꡢ���ϾA������
	���ԣ���Ҫͣ�������� 
*/
const int N = 1e5+5;
struct edge{int v,nxt;}e[N<<1];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
struct node{
	int lson,rson,sum,maxx;
	#define lson(x) t[x].lson
	#define rson(x) t[x].rson
	#define sum(x) t[x].sum
	#define maxx(x) t[x].maxx
}t[N<<4];//
int c[N];
int rootc[N];
int n,m;
struct segment_tree{
	int tot;
	inline void pushup(int rt){
		sum(rt) = sum(lson(rt)) + sum(rson(rt));
		maxx(rt) = max(maxx(lson(rt)), maxx(rson(rt)));
	}
	inline void update(int &rt,int l,int r,int pos,int val){
		if(!rt) rt = ++tot;
		if(l==r){
			sum(rt) = maxx(rt) = val;
			return;
		}
		if(pos <= mid) update(lson(rt),l,mid,pos,val);
		else update(rson(rt),mid+1,r,pos,val);
		pushup(rt);
	}
	inline int query_max(int rt,int l,int r,int L,int R){
		if(!rt) return 0;
		if(L<=l && r<=R) return maxx(rt);
		int ret = 0;
		if(L<=mid) ret = max(ret,query_max(lson(rt),l,mid,L,R));
		if(R> mid) ret = max(ret,query_max(rson(rt),mid+1,r,L,R));
		return ret;
	}
	inline int query_sum(int rt,int l,int r,int L,int R){
		if(!rt) return 0;
		if(L<=l && r<=R) return sum(rt);
		int ret = 0;
		if(L<=mid) ret += query_sum(lson(rt),l,mid,L,R);
		if(R> mid) ret += query_sum(rson(rt),mid+1,r,L,R);
		return ret;
	}
}seg;
int id[N],idx,top[N],dep[N],w[N],hson[N],size[N],fa[N];
inline void dfs1(int x,int f){
	size[x] = 1;
	fa[x] = f;dep[x] = dep[f] + 1;
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
	top[x] = topx;
	if(!hson[x]) return;
	dfs2(hson[x],topx);
	for(int i=h[x];i;i=e[i].nxt){
		int v = e[i].v;
		if(v==fa[x] || v==hson[x]) continue;
		dfs2(v,v);
	}
}
inline int Qsum(int x,int y){
	int sum = 0;
	//��ѯ���ڽ̾�û�б�����Ҹ�������
	int root = rootc[c[x]];
	while(top[x]!=top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		sum += seg.query_sum(root,1,n,id[top[x]],id[x]);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	sum += seg.query_sum(root,1,n,id[x],id[y]);
 	return sum;
}
inline int Qmax(int x,int y){
	int ret = 0;
	int root = rootc[c[x]];//����de����bug��ʱ���ȥ���Ⱑ������ 
	while(top[x]!=top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		ret = max(ret, seg.query_max(root,1,n,id[top[x]],id[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	ret = max(ret, seg.query_max(root,1,n,id[x],id[y]));
 	return ret;
}
int a,b;
char ins[10];
int main(){
//	freopen("q20.in","r",stdin); 
//	freopen("my.out","w",stdout);
	io >> n >> m;
	for(int i=1;i<=n;i++){
		io >> w[i] >> c[i];
	}
	for(int i=1;i<n;i++){
		io >> a >> b;
		add(a,b),add(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);

	for(int i=1;i<=n;i++){
//		seg.update(rootc[c[rid[i]]],1,n,i,w[rid[i]]);//��ôд�ѿռ�һЩ 
		seg.update(rootc[c[i]],1,n,id[i],w[i]);//��ôдҲ�ԣ��������ڵ�������˳��ͬ 
	}
	for(int i=1;i<=m;i++){
		scanf("%s",ins);
		io >> a >> b;
		if(ins[0]=='C'){
			if(ins[1]=='C'){//a�Ǹ���b
				seg.update(rootc[c[a]],1,n,id[a],0);//del����������0 
				c[a] = b;
				seg.update(rootc[c[a]],1,n,id[a],w[a]);
			}else{//a��������Ϊb
				seg.update(rootc[c[a]],1,n,id[a],0);
				w[a] = b;
				seg.update(rootc[c[a]],1,n,id[a],w[a]);
			}
		}else{
			if(ins[1]=='S'){//��ѯ����sum
				io << Qsum(a,b) << '\n';
			}else{//��ѯ����max
				io << Qmax(a,b) << '\n';
			}
		}
	}
	return 0;
}
