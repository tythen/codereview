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
草一开始想歪了：然后越走越远。
因为我们必须考虑那个起始点，所以想办法把他的权值弄进生成树里面 ，最后就是超级原点的思想 
最小生成树：选最便宜的点 做prim，如果一个点直接加比连边便宜，那就直接加点呀
像这种并列起始的思想：真的就是要想到超级原点啊 
*/
const int N = 500000;
struct node{
	int v;ll dis;
	friend bool operator < (const node a,const node b){
		return a.dis > b.dis;
	}
};
int e[505][505];
int n,vis[N];
ll w[N];
priority_queue <node> q;
inline ll prim()
{
	ll ans = 0;
	vis[0] = 1;
	for(int i=1;i<=n;i++) 
		q.push((node){i,w[i]});
	while(!q.empty())
	{
		node now = q.top();q.pop();
		int x = now.v;
		if(vis[x]) continue;
		ans += now.dis;
		vis[x] = 1;
		for(int i=1;i<=n;i++)
		{
			if(!vis[i]) q.push((node){i,e[x][i]});
		}
	}
	return ans;
}
int main()
{
//	freopen("water.8.in","r",stdin);
	io >> n;
	up(i,1,n) io >> w[i];
	up(i,1,n) up(j,1,n) io >> e[i][j];
	ll ans = prim();
	io << ans;
	return 0;
}
