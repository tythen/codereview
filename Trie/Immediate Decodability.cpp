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
const int N = 1e4+5;
struct Trie{
	int son[N][12],tot,end[N];
	inline bool insert(char *s)
	{
		int len = strlen(s+1),rt = 0,flag = 0;
		up(i,1,len)
		{
			int v = s[i] - '0';
			if(!son[rt][v]) son[rt][v] = ++tot;
			rt = son[rt][v];
			flag |= end[rt];
 		}
		end[rt] = 1;
		up(i,0,10) if(son[rt][i]) flag = 1;
		return flag;
	}
	inline void init()
	{
		memset(son,0,sizeof son);
		memset(end,0,sizeof end);
		tot = 0;
	}
}t;
int n,cnt;
char s[100];
int main()
{
	int flag = 0;
	while(scanf("%s",s+1)!=EOF)
	{
		if(s[1]=='9' && s[2]=='\0')
		{
			++cnt;
			if(flag) printf("Set %d is not immediately decodable\n",cnt);
			else printf("Set %d is immediately decodable\n",cnt);
			t.init();
			flag = 0;
			continue;
		}
		flag |= t.insert(s);
	}
	return 0;
}
