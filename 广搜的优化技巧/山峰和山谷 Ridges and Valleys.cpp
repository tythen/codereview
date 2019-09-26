#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>

#define ll long long
#define pau system("pause")
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
const int p = 13331;
const int N = 1005;
/*
先把所有同高度块都标成 一个颜色
然后对每个颜色：跑周围有没有比自己高的或者低的标记type 
*/
int dx[] = {0,0,1,-1,1,1,-1,-1};
int dy[] = {1,-1,0,0,1,-1,1,-1};
int T,L,pic[N][N];
int col[N][N],cnt;
int type[N*N];
struct stage{int x,y;};
queue <stage> q;
inline void bfs_color(int sx,int sy)
{
	while(!q.empty()) q.pop();
	q.push((stage){sx,sy});
	col[sx][sy] = ++cnt;
	while(!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		q.pop();
		for(int i=0;i<8;i++)
		{
			int xx = x+dx[i];
			int yy = y+dy[i];
			if(xx>=1 && xx<=L && yy>=1 && yy<=L)
			{
				if(pic[xx][yy] == pic[sx][sy] && !col[xx][yy]) 
				{
					q.push((stage){xx,yy});
					col[xx][yy] = cnt;
				}
			}
		}
	}
}
int vis[N][N];
inline void bfs_gettype(int sx,int sy)
{
	while(!q.empty()) q.pop();
	q.push((stage){sx,sy});
	while(!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		q.pop();
		for(int i=0;i<8;i++)
		{
			int xx = x+dx[i];
			int yy = y+dy[i];
			if(xx>=1 && xx<=L && yy>=1 && yy<=L)
			{
				if(col[xx][yy] == col[sx][sy] && !vis[xx][yy]) 
				{
					vis[xx][yy] = 1;
					q.push((stage){xx,yy});
				}
				else
				{
					if(!type[col[sx][sy]] && pic[xx][yy] > pic[sx][sy]) type[col[sx][sy]] = 1;//是山谷
					else if(!type[col[sx][sy]] && pic[xx][yy] < pic[sx][sy]) type[col[sx][sy]] = 2;//是山峰
					if(type[col[sx][sy]]==1 && pic[xx][yy] < pic[sx][sy]) type[col[sx][sy]] = -1;//什么都不是
					else if(type[col[sx][sy]]==2 && pic[xx][yy] > pic[sx][sy]) type[col[sx][sy]] = -1;//什么都不是
				}
				if(type[col[sx][sy]] == -1) return;
			}
		}
	}	
}

int main()
{
	io >> L;
	up(i,1,L) up(j,1,L) io >> pic[i][j];
	up(i,1,L) up(j,1,L)
	{
		if(!col[i][j]) bfs_color(i,j);
	}
	
	up(i,1,L) up(j,1,L) if(!vis[i][j]) bfs_gettype(i,j);
	int ans2 = 0,ans1 = 0;
	up(i,1,cnt) 
	{
		ans2 += (type[i] == 2);
		ans1 += (type[i] == 1);
	}
	if(cnt==1) ans2 = ans1 = 1;
	io << ans2 << ' ' << ans1;
}
