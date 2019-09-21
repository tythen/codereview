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
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
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
const int N = 5e5+5;
const int inf = 0x7f7f7f7f;
struct edge{
	int v,nxt;ll w;
}e[N<<1];
struct node{
	ll dis,x;
	friend bool operator < (const node a,const node b){
		return a.dis > b.dis;
	}
};
int h[N],tot;
inline void add(int x,int y,ll w){
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
ll dis[N];
int vis[N];
int n,m,s;
priority_queue <node> q;
inline void dijkstra(int st){
	up(i,1,n) dis[i] = 0x7f7f7f7f;
	dis[st] = 0;
	q.push((node){0,st});
	while(!q.empty()){
		int x = q.top().x;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		Auto(i,x){
			int v=e[i].v;
			if(dis[v] > dis[x] + e[i].w){
				dis[v] = dis[x] + e[i].w;
				q.push((node){dis[v],v});
			}
		}
	}
}
ll a,b,c;
int main(){
	freopen("castle7.in","r",stdin);
	io >> n >> m >> s;
	up(i,1,m){
		io >> a >> b >> c;
		add(a,b,c);
	}
	dijkstra(s);
	up(i,1,n) io << dis[i] << ' ';
 	return 0;
}
