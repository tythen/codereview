#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<limits>

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
}io;
const ll inf = 0x7f7f7f7f;
inline ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0){x=1,y=0;return a;}
	ll d = exgcd(b,a%b,x,y);
	ll xx = x;
	x = y,y = xx - (a/b)*y;
	return d;
}
/*
以下字母与原题字母无关 
pa + ax ≡pb + bx (% L)
ax - bx + mL = pb - pa + nL
(a-b)x + (m-n)L = pb-pa
A = (a-b)
B = L
C = pb - pa
Ax + B(m-n) = C
*/
ll x,y,A,B,C,pa,pb,a,b,L;
int main()
{
	io >> pa >> pb >> a >> b >> L;
	if(a < b) swap(a,b),swap(pa,pb);
	A = a-b,B = L,C = pb - pa;
	ll d = exgcd(A,B,x,y);
	if(C%d != 0) {
		puts("Impossible");
		return 0;
	}
	x *= (C/d) , y *= (C/d);
	io << (x%(B/d) + (B/d))%(B/d);
//	while(x < 0) x += (B/d),y -= (A/d);
//	io << x%(B/d);
	return 0;
}
