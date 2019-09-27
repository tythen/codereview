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
const int N = 200;
/*
一共有5种操作：
上下左右正常地搜
关于“选择 ” 可以保存当前stage所拿着的字符串 与 目标字符串匹配的 位置，每次判断是否光标的字符是需要的，如果是就 “选择”


写的时候vis应该预先标-1，因为可能开始pos为0，这时也视作来过不过pos小
然后预处理每个位置各个方向上下一个位置在哪里免得再跳 
*/
#define num(x,y) ((x-1)*m+y)
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
//map <pair<int,int> ,int> ma;
struct stage{int x,y,step,pos;};
queue <stage> q;
int n,m;
char ed[10005];
char pic[N][N];
int vis[N*N];
pair<int,int> jup[5][N][N];
int len;
inline int bfs()
{
	q.push((stage){1,1,0,0});
	while(!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int step = q.front().step;
		int pos = q.front().pos;
		q.pop();
		if(pic[x][y] == ed[pos+1])
		{
			if(vis[num(x,y)]==-1 || vis[num(x,y)] < pos+1)
			{
				q.push((stage){x,y,step+1,pos+1});
				vis[num(x,y)] = pos+1;
			}
			if(pos+1 == len) return step+1;
		}
		up(i,0,3)
		{
			int xx = x + dx[i];
			int yy = y + dy[i];
			xx = jup[i][x][y].first,
			yy = jup[i][x][y].second;
			if(xx>=1 && xx<=n && yy>=1 && yy<=m)
			{
				if(vis[num(xx,yy)]==-1 || vis[num(xx,yy)] < pos)
				{
					q.push((stage){xx,yy,step+1,pos});
					vis[num(xx,yy)] = pos; 
				}
			}
		}
	}
	return -1;
}

int main()
{
	io >> n >> m;
	up(i,1,n) scanf("%s",pic[i]+1);
	scanf("%s",ed+1);
	len = strlen(ed+1);
	ed[++len] = '*';ed[len+1] = '\0';
	
	up(i,1,n) up(j,1,m)
	{
		up(d,0,3)
		{
			int xx = i+dx[d],yy = j+dy[d];
			while(pic[xx][yy] == pic[i][j]) xx += dx[d],yy += dy[d];
			jup[d][i][j] = make_pair(xx,yy);
		}
		vis[num(i,j)] = -1;
	}
	
	io << bfs();
	return 0;
}
