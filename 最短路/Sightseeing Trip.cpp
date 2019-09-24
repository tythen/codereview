#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>

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
floyd可以解决一类 给一个正权无向图，找一个最小权值和的环 的问题 
这个题学会了k的阶段意义，Floyd存路径的方式 
80分原因：把0x3f 改成0x1f就过了 
*/
const int N = 205;
ll dis[N][N],e[N][N],pre[N][N];
ll n,m,a,b,c; 
vector <int> path;
inline void get_path(int x,int y)
{
	if(pre[x][y]==0) return;
	get_path(x,pre[x][y]);
	path.push_back(pre[x][y]);//递归分治的方式通过保存的pre得到路径 
	get_path(pre[x][y],y);
}
int main()
{
	io >> n >> m;
//	memset(dis,0x1f,sizeof dis);
//	memset(e,0x1f,sizeof e);//用mem有危险，为何不直接平方赋值，更快很精确 
	up(i,1,n) up(j,1,n) dis[i][j] = dis[j][i] = e[i][j] = e[j][i] = 0x3f3f3f3f;
	up(i,1,m)
	{
		io >> a >> b >>  c;
		dis[a][b] = dis[b][a] = min(dis[a][b],c);
		e[a][b] = e[b][a] = min(e[a][b],c);
	}
	ll ans = 0x3f3f3f3f;
	for(register int k=1;k<=n;k++)
	{
		for(register int i=1;i<k;i++)
		{
			for(register int j=i+1;j<k;j++)
			{
				if(ans > (ll)(dis[i][j] + e[i][k] + e[k][j]))
				{
					ans = dis[i][j] + e[i][k] + e[k][j];
					path.clear();
					get_path(i,j);
					path.push_back(j);
					path.push_back(k);
					path.push_back(i);
				}
			}
		}
		
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=n;j++)
			{
				if(i==j) continue;
				if(dis[i][j] > dis[i][k] + dis[k][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					pre[i][j] = k;//pre 保存以前ij相连时的中间点k 
				}
			}
		}
	}
	
	if(ans == 0x3f3f3f3f || path.size()<3) puts("No solution.");
	else 
	{
		int t = path.size();
		for(int i=0;i<t;i++) io << path[i] <<' ';
	}
	return 0;
}

 
