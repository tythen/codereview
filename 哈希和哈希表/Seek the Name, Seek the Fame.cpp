#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>

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
		up(i,1,n) H[i] = 0;
		up(i,1,n) H[i] = H[i-1] * p + s[i];
	}
	inline ull hash(int l,int r)
	{
		return H[r] - H[l-1] * power[r-l+1];
	}
}S;
int len;

char s[N];
vector <int> ans;
int main()
{
	power[0] = 1;up(i,1,1e6) power[i] = power[i-1] * p;
	while(scanf("%s",s+1) != EOF)
	{
		ans.clear();
		int len = strlen(s+1);
		S.init(s,len);
		up(i,1,len) if(S.hash(1,i) == S.hash(len-i+1,len)) ans.push_back(i);
		up(i,0,ans.size()-1) io << ans[i] << ' ';io <<'\n';
	}
	return 0;
}
