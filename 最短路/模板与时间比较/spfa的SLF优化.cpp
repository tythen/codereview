#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<limits>

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
const int N = 1e6+5;
const int inf = numeric_limits <int> :: max(); 
struct edge{int v,nxt;ll w;}e[N<<1];
int h[N],tot;
inline void add(int x,int y,ll w)
{
	e[++tot] = (edge){y,h[x],w};
	h[x] = tot;
}
int vis[N],n,m;
ll dis[N];

deque <int> q;
inline void spfa(int st)//仍然过不了 luogu的强化数据 
{
	up(i,1,n) dis[i] = inf,vis[i] = 0;
	dis[st] = 0;
	q.push_front(st);
	while(!q.empty())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		Auto(i,x)
		{
			int v = e[i].v;
			if(dis[v] > dis[x] + e[i].w)
			{
				dis[v] = dis[x] + e[i].w;
				if(!vis[v])
				{
					vis[v] = 1;
					if(!q.empty() && dis[v] < dis[q.front()]) q.push_front(v);
					else q.push_back(v);
				}
			}
		}
	}
}


ll a,b,c;
int st;
int main()
{
	io >> n >> m >> st;
	up(i,1,m)
	{
		io >> a >> b >> c;
		add(a,b,c);
	}
	spfa(st);
	up(i,1,n) io << dis[i] << ' ';
	return 0;
}
