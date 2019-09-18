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
const int p = 13331;
ull power[N];
struct Hash{
	ull H[N];
	inline void init(char *s,int n)
	{
		for(int i=1;i<=n;i++) H[i] = 0;
		for(int i=1;i<=n;i++) H[i] = H[i-1] * p + s[i]-'A';
	}
	inline ull hash(int l,int r)
	{
		return H[r] - H[l-1] * power[r-l+1];
	}
	inline ull merge(int l1,int r1,int l2,int r2)
	{
		return hash(l1,r1) * power[r2-l2+1] + hash(l2,r2);
	}
}S;
int len;
ull only=-1;
char s[N];//删一个字符，从中间分开
int cnt,pos; 
int main()
{
	power[0] = 1;up(i,1,1e6) power[i] = power[i-1] * p;
	io >> len;
	scanf("%s",s+1);
	S.init(s,len);
	if(len%2==0) {puts("NOT POSSIBLE");return 0;}
	int half = (len-1)/2;
	for(int i=1;i<=len;i++)
	{
		ull h1,h2;
		if(i<=half) h1 = S.merge(1,i-1,i+1,half+1),h2 = S.hash(half+2,len);
		else h1 = S.hash(1,half),h2 = S.merge(half+1,i-1,i+1,len);
		ull hh = S.merge(1,i-1,i+1,len);
		if(h1==h2)
		{
			if(only==-1) only = hh,cnt++;
			else if(only!=hh) cnt++;
			pos = i;
		}
		if(cnt>=2) 
		{
			break;
		}
	}
	if(cnt==0) puts("NOT POSSIBLE");
	else if(cnt >= 2) puts("NOT UNIQUE");
	else for(int i=1;half;i++) if(i!=pos) io << s[i],half--;
	return 0;
}
