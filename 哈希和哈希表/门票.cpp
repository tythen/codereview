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
const int p = 1999993;
struct Hash_table{
	struct node{
		int key,val,nxt;
	}e[N];
	int h[N],tot;
	inline void change(ull key,int val)
	{
		for(int i=h[key%p];i;i=e[i].nxt)
		{
			if(e[i].key == key) e[i].val = val;
		}
		e[++tot] = (node){key,val,h[key%p]};
		h[key%p] = tot;
	}
	inline int operator [] (ull key)
	{
		for(int i=h[key%p];i;i=e[i].nxt)
		{
			if(e[i].key == key) return e[i].val;
		}
		return 0;
	}
}ha;
ll A,B,C;
ll ai = 1;
int main()
{
	io >> A >> B >> C;
	ha.change(ai,1);
	for(int i=1;i<=2000000;i++)
	{
		ai = (A*ai + ai%B)%C;
		int tp = ha[ai];
		if(tp > 0)
		{
			io << i;
			return 0;
		}
		ha.change(ai,1);
	}
	puts("-1");
	return 0;
}
