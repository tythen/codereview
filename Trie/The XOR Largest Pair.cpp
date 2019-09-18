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
	inline int rd(){
		int x;*this >> x;return x;
	}
}io;
const int N = 2e6+5;
struct Trie{
	int tot,son[N][2],end[N],len;//这种题一定要统一最长长度 
	inline void insert(int a)
	{
		int rt = 0;
		int tp = a;
		up(i,1,len)
		{
			int b = (a>>(len-i)) & 1;
			if(!son[rt][b]) son[rt][b] = ++tot;
			rt = son[rt][b];
		}
		end[rt] = a;
	}
	inline int query(int a)
	{
		int rt = 0,ans = 0;
		up(i,1,len)
		{
			int b = (a>>(len-i)) & 1;
			if(son[rt][b^1]) rt = son[rt][b^1],ans = (ans<<1) + (b^1);
			else rt = son[rt][b],ans = (ans<<1) + b;
		}
		return a^end[rt];
	}
}t;

int T,n;
int a[N];
int ans;
int main()
{
	io >> n;
	up(i,1,n) 
	{
		io >> a[i];
		int tp = a[i],tlen = 0;
		while(tp) tlen++,tp>>=1;
		t.len = max(tlen,t.len);
	}
	up(i,1,n) t.insert(a[i]);
	up(i,1,n) ans = max(ans,t.query(a[i]));
	io << ans;
	return 0;
}
