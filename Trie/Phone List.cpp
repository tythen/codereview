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
	inline int rd(){
		int x;*this >> x;return x;
	}
}io;
const int N = 2e5+5;
struct Trie{
	int tot,son[N][15],end[N];
	inline bool insert(char *s)//2种情况，向下跳的时候路过一个end，跳到末尾发现下面有多的节点 
	{
		int flag = 0;
		int rt = 0,len = strlen(s+1);
		up(i,1,len)
		{
			int v = s[i]-'0';
			if(!son[rt][v]) son[rt][v] = ++tot;
			flag |= end[rt];
			rt = son[rt][v];
		}
		up(v,0,10) if(son[rt][v]) flag=1;//如果结尾存在后续节点，说明还有串在后面
		end[rt] = 1; 
		return flag;
	}
	inline void init()
	{
		tot=0;
		memset(end,0,sizeof end);
		memset(son,0,sizeof son);
	}
}t;

int T,n;
char s[100];
int main()
{
	io >> T;
	while(T--)
	{
		t.init();
		int flag = 0;
		io >> n;
		while(n--)
		{
			scanf("%s",s+1);
			flag |= t.insert(s);
		}
		if(flag) puts("NO");
		else puts("YES");
	}
	return 0;
}
