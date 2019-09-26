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
const ll inf = 0x7f7f7f7f;
const int p = 13331;
const int N = 2e5+5;
/*
œ∏Ω⁄¬È∑≥Ã‚∑≥À¿¡À 
*/
int st[8][8],ed[8][8];
ll S,E;
map <ll,int> vis;
struct node{
	ll stage,step;
};
inline void write(ll s)
{
	int cnt = 0;
	for(int i=15;i>=0;i--)
	{
		cout<< ((s>>i)&1);
		cnt++;
		if(cnt==4) puts(""),cnt=0;
	}
	cout << endl;
}
queue <node> q;
inline int bfs()
{
	vis[S] = 1;
	q.push((node){S,0});
	while(!q.empty())
	{
		ll now = q.front().stage;
		ll step = q.front().step;
		q.pop();
		if(now == E) return step;
//		printf("step = %d\n",step);
//		write(now);
		for(int i=4;i<=15;i++)
		{
			if(((now>>i) & 1) ^ ((now>>(i-4)) & 1)) 
			{
				ll nxt = now;
				nxt ^= (1<<i);
				nxt ^= (1<<(i-4));
				if(!vis[nxt]) q.push((node){nxt,step+1,}),vis[nxt]=1;
			}
		}
		for(int i=1;i<=15;i++)
		{
			if(i%4==0) continue;
			if(((now>>i) & 1) ^ ((now>>(i-1)) & 1))
			{
				ll nxt = now;
				nxt ^= (1<<i);
				nxt ^= (1<<(i-1));
				if(!vis[nxt]) q.push((node){nxt,step+1}),vis[nxt]=1;
			}
		}
	}
	return 19260817;
}

int main()
{
	up(i,1,4) up(j,1,4) 
	{
		scanf("%1d",&st[i][j]);
		S <<= 1;
		S |= st[i][j];
	}
	up(i,1,4) up(j,1,4) 
	{
		scanf("%1d",&ed[i][j]);
		E <<= 1;
		E |= ed[i][j];
	}
	cout << bfs();
	return 0;
}
