#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>

#define ll long long
#define ull unsigned ll
#define re register
#define isa(c) (c>='0' && c<='9')
#define up(i,a,b) for(register int i=a;i<=b;++i)
#define down(i,a,b) for(register int i=a;i>=b;--i)
#define Auto(i,x) for(register int i=h[x];i;i=e[i].nxt)
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x){
		re char c=getchar();int f=1;x=0;
		for(;!isa(c);c=getchar()) if(c=='-') f=-1;
		for(;isa(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x){
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
/*
二分+建图判断 
spfa判定 
*/
const int N = 2000;
struct edge{int v,nxt,w;}e[N<<1];
struct node{int x,y,w;}oe[N<<1];
int tot,h[N];
inline void add(int x,int y,int w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
queue <int> q;
int dis[N],vis[N];
int n,k,m;
inline bool check(int x)
{
	up(i,1,n) h[i] = 0,dis[i] = 0x7f7f7f7f;
	tot = 0; 
	up(i,1,m)
	{
		add(oe[i].x,oe[i].y, oe[i].w>x ? 1:0);
		add(oe[i].y,oe[i].x, oe[i].w>x ? 1:0);
	}
	dis[1] = 0;
	q.push(1);
	while(!q.empty())
	{
		int it = q.front();q.pop();
		vis[it] = 0;
		Auto(i,it)
		{
			int v = e[i].v;
			if(dis[v] > dis[it] + e[i].w)
			{
				dis[v] = dis[it] + e[i].w;
				if(!vis[v]) vis[v] = 1,q.push(v);
			}
		}
	}
	return dis[n] <= k;//二分的写法 需要给予单调性 
}


int main()
{
	io >> n >> m >> k;
	int l = 0,r = -0x7f7f7f7f;
	up(i,1,m)
	{
		io >> oe[i].x >> oe[i].y >> oe[i].w;
		l = min(l,oe[i].w);
		r = max(r,oe[i].w);
	}
	int ans = -1;
	while(l <= r)
	{
		int mid = l+r >> 1;
		if(check(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	}
	io << ans;
	return 0;
}
