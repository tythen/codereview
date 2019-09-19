#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>

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
	inline int rd(){int x;*this >> x;return x;}
}io;
const int N = 2e6+5; 
int ret[N];
int nxt[N];
inline int dfs(int x)
{
	if(x==0) return 0;
	if(ret[x] != -1) return ret[x];
	int tp = dfs(nxt[x]);
	if(tp) return ret[x] = tp;
	else return ret[x] = x;
}
inline void make_nxt(char *P,int len)
{
	nxt[1] = 0;int j = 0;
	for(int i=2;i<=len;i++)
	{
		while(j>0&&P[i] != P[j+1]) j = nxt[j];
		if(P[i] == P[j+1]) j++;
		nxt[i] = j;
	}
}

char P[N];
int lenP;
ll ans;
int main()
{
	io >> lenP;
	scanf("%s",P+1);
	make_nxt(P,lenP);
	up(i,1,lenP) ret[i] = -1;
	for(int i=lenP;i>=1;i--)
	{
		int j = dfs(i);
		ans += i - j;
		/*
		另一种写法：
		while(nxt[j]) j=nxt[j];
		if(nxt[i]) nxt[i]=j;//记忆化 直接把这一位前面的都不管了 比我快 
		ans+=i-j; 
		*/
	}
	io << ans;
	return 0;
}
