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
int l[N],r[N];
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
char T[N],P[N],ans[N];
int lenT,lenP,cnt,f[N];
int main()
{
	scanf("%s%s",T+1,P+1);
	lenT = strlen(T+1);
	lenP = strlen(P+1);
	make_nxt(P,lenP);
	for(int i=1;i<=lenT;i++) l[i] = i-1,r[i] = i+1;
	r[0] = 1;
	l[lenT+1] = lenT;
	for(int i=1,j=0;i<=lenT;i=r[i])//用链表 
	{
		while(j>0 && (j==lenP ||T[i] != P[j+1])) j = nxt[j];
		if(T[i] == P[j+1]) j++;
		f[i] = j;
		if(j==lenP)
		{
			int R = r[i];
			up(tp,1,lenP) i = l[i];//向左跳lenP次 
			r[i] = R;
			l[R] = i;
			j = f[i];
		}
	}
	for(int i=r[0];i!=lenT+1;i=r[i]) io << T[i];
	return 0;
}
