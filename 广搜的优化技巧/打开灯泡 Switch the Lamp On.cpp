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
const ll inf = 0x7f7f7f7f;
int n,m;
char s[505][505];
int vis[505][505];
struct stage{int step,x,y;};
int dx[] = {1,1,-1,-1};
int dy[] = {1,-1,1,-1};
int ddx[] = {0,0,-1,-1};
int ddy[] = {0,-1,0,-1};
deque <stage> q;
int main()
{
	io >> n >> m;
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	q.push_front((stage){0,1,1});
	while(!q.empty())
	{
		stage it = q.front();q.pop_front();
		int step = it.step;
//		io << it.x << ' ' << it.y << '\n';
		if(vis[it.x][it.y]) continue;
		vis[it.x][it.y] = 1;
		if(it.x == n+1 && it.y == m+1)
		{
			io << it.step;
			return 0;
		} 
		for(int d=0;d<4;d++)
		{
			int xx = it.x + dx[d],dxx = it.x + ddx[d];
			int yy = it.y + dy[d],dyy = it.y + ddy[d];
			if(xx >= 1&&xx <= n+1 && dxx >= 1 && dxx <= n && (yy >= 1&&yy <= m+1 && dyy >= 1 && dyy <= m))
			{
				if((d==0 || d==3))
				{
					if((s[dxx][dyy]=='\\')) q.push_front((stage){step,xx,yy});
					else q.push_back((stage){step+1,xx,yy});
				}
				else
				{
					if((s[dxx][dyy]=='/')) q.push_front((stage){step,xx,yy});
					else q.push_back((stage){step+1,xx,yy});
				}
			}
		}
	}
	puts("NO SOLUTION");
	return 0;
}
