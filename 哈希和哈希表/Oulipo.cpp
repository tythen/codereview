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
const int N = 1e6+5; 
const int mod = 13331;
ull power[N];

struct Hash{
	ull H[N];
	int len;
	inline void init(int n,char *s)
	{
		len = n;
		up(i,1,n)//hash将其变为mod进制数，左边的为高位 
			H[i] = H[i-1] * mod + (s[i]-'A'+1);//'A' < 'a'
	}
	inline ull hash(int l,int r)
	{
		return H[r] - H[l-1] * power[r-l+1];
	}
}S,T;


char s1[N],s2[N];
int main()
{
	power[0] = 1;
	up(i,1,1e6) power[i] = power[i-1]*mod;	
	scanf("%s\n%s",s1+1,s2+1);
	S.init(strlen(s1+1),s1);
	T.init(strlen(s2+1),s2);
	int ans = 0;
	for(int i=1;i+T.len-1<=S.len;i++) 
		ans += (S.hash(i,i+T.len-1) == T.hash(1,T.len));
	io << ans;
	return 0;
}
