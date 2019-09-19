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
int nxt[N];
inline void make_nxt(char *P,int len)
{
	for(int i=1;i<=len;i++) putchar(P[i]);puts("");
	nxt[1] = 0;
	int j = 0;
	for(int i=2;i<=len;i++)
	{
		while(j>0 && P[i] != P[j+1]) j = nxt[j];
		if(P[i] == P[j+1]) j++;
		nxt[i] = j;
	}
}
inline int match(char *T,char *P,int lenT,int lenP)
{
	int j = 0,ans = 0;
	for(int i=1;i<=lenT;i++)
	{
		while(j>0 && T[i] != P[j+1]) j = nxt[j];
		if(T[i] == P[j+1]) j++;
		if(j==lenP)
		{
			ans ++ ;
			j = 0;
		}
	}
	return ans;
}

char T[N],P[N];
int lenT,lenP;
int main()
{
	io >> lenT;
	scanf("%s",T+1);
	up(i,1,lenT) T[i+lenT] = T[i];
	puts(T+1);
	*P = *T;
//	lenT = strlen(T+1);
	make_nxt(T,lenT);
		up(i,1,lenT) io << nxt[i] << ' ';puts("");
	for(int k=1;k<lenT;k++)
	{
		T[lenT*2+k] = T[k];T[lenT*2+k+1] = T[k] = '\0';
		make_nxt(T+k,lenT);
		up(i,1,lenT) io << nxt[i] << ' ';puts("");
	}
}
