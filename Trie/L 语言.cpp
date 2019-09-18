#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

#define ll long long
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
	inline int rd(){int x;*this >> x;return x;}
}io;
const int N = 8e6+5;
int vis[N];
struct Trie{
	int son[N][30],tot,end[N];
	inline void insert(char *s)
	{
		int len = strlen(s),rt = 0;
		up(i,0,len-1)
		{
			int v = s[i] - 'a';
			if(!son[rt][v]) son[rt][v] = ++tot;
			rt = son[rt][v];
		}
		end[rt] = len;
	}
	inline void query(char *s,int len,int nd,int &ans)
	{
		int rt = 0;
		up(i,nd,len-1)
		{
			int v = s[i] - 'a';
			if(!son[rt][v]) return;
			rt = son[rt][v];
			if(end[rt])
			{
				ans = max(ans,i+1);
				vis[i+1] = 1;
			}
		}
	}
}t;
int n,m;
char s[1000000+10];
int main()
{
	io >> n >> m;
	up(i,1,n)
	{
		scanf("%s",s+1);
		t.insert(s+1);
	}
	up(i,1,m)
	{
		scanf("%s",s);
		int len = strlen(s);
		int ans = 0;
		vis[0] = 1;
		up(j,0,len-1) 
			if(vis[j]) 
				t.query(s,len,j,ans);//本质上是暴力dfs的优化，把后面能作起搜点的标出来，就可避免深搜 
		up(j,0,len-1) vis[j] = 0;
		io << ans << '\n';
	}
	return 0;
}
