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
const int N = 2e5+5;
/*

*/
int dx[] = {-2,-1,1,2,2,1,-1,-2};
int dy[] = {1,2,2,1,-1,-2,-2,-1};

int T,L,pic[305][305];
struct stage{int x,y,step;};
queue <stage> q;
int stx,sty,edx,edy;
inline int bfs1(int sx,int sy,int stop)
{
	while(!q.empty()) q.pop();
	q.push((stage){sx,sy,0});
	while(!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int step = q.front().step;
		q.pop();
//		if(step >= stop) break;
		if(x == edx && y == edy) return step;
		for(int i=0;i<8;i++)
		{
			int xx = x+dx[i];
			int yy = y+dy[i];
			if(xx>=0 && xx<=L && yy>=0 && yy<=L)
			{
				if(!pic[xx][yy])
				{
					pic[xx][yy] = step+1;
					q.push((stage){xx,yy,step+1});
				}
			}
		}
	}
	return -1;
}
//inline int bfs2(int sx,int sy)
//{
//	while(!q.empty()) q.pop();
//	q.push((stage){sx,sy,0});
//	while(!q.empty())
//	{
//		int x = q.front().x;
//		int y = q.front().y;
//		int step = q.front().step;
//		q.pop();
//		for(int i=0;i<8;i++)
//		{
//			int xx = x+dx[i];
//			int yy = y+dy[i];
//			if(xx>=0 && xx<=L && yy>=0 && yy<=L)
//			{
//				if(pic[xx][yy]==0)
//				{
//					pic[xx][yy] = -step-1;//为了区别正向搜和反向搜用了负数 
//					q.push((stage){xx,yy,step+1});
//				}
//				if(pic[xx][yy] > 0)
//				{
//					return step+1+pic[xx][yy];
//				}
//			}
//		}
//	}	
//	return -1;
//}
int main()
{
	io >> T;
	while(T--)
	{
		io >> L;
		up(i,0,L) up(j,0,L) pic[i][j] = 0;
		io >> stx >> sty >> edx >> edy;
		if(stx == edx && sty == edy)
		{
			puts("0");
			continue;
		}
		int flag = bfs1(stx,sty,(abs(stx-edx)+abs(sty-edy)) / 2);
//		if(flag==-1) io << bfs2(edx,edy) << '\n';
//		else
		 io << flag << '\n';
	}
	return 0;
}
