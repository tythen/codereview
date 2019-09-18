#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
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
const int p = 13331;
ull power[N];
struct Hash{
	ull H[N];
	int len;
	inline void init(char *s,int n)
	{
		len = n;
		for(int i=1;i<=n;i++) H[i] = 0;
		for(int i=1;i<=n;i++) H[i] = H[i-1] * p + (s[i]);
	}
	inline ull hash(int l,int r)
	{
		return H[r] - H[l-1] * power[r-l+1];
	}
}S;
int len;
inline bool check(int tlen)
{
	if(len % tlen != 0) return 0;
	int now = 1;
	while(now!=len+1)
	{
		if(S.hash(1,tlen) == S.hash(now,now+tlen-1)) now += tlen;
		else return 0;
	}
	return 1;
}
char s1[N];
int nxt[N];
int list[1000];
int main()
{
	power[0] = 1;up(i,1,1e6) power[i] = power[i-1] * p;
	while(scanf("%s",s1+1)!=EOF)
	{
		if(s1[1]=='.') return 0;
		len = strlen(s1+1);
		S.init(s1,len);
		memset(list,0,sizeof list);
		for(int i=len;i>=1;i--) 
		{
			nxt[i] = list[s1[i]];
			list[s1[i]] = i;
		}
		int now = nxt[1],tlen = now-1;
		if(nxt[1]==0)
		{
			io << 1 << '\n';
			continue;
		}
		while(now != 0&&now!= len)
		{
			if(check(tlen)) break;
			now = nxt[now],tlen = now-1;
		}
		if(now==0) tlen = len;
		io << len / tlen << '\n';
//		for(int i=1;i<=len;i++) io << nxt[i] << ' ';puts("");
//		for(int i=1;i<=len;i++) list[s1[i]] = 0;
	}
	return 0;
}
