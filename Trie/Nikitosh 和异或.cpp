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
	inline int rd(){int x;*this >> x;return x;}
}io;
const int N = 8e6+5;
struct Trie{
	int son[N][2],tot,end[N];
	inline bool insert(int s)
	{
		int rt = 0;
		down(i,31,0)
		{
			int b = (s >> i) & 1;
			if(!son[rt][b]) son[rt][b] = ++tot;
			rt = son[rt][b];
		}
		end[rt] = s;
	}
	inline int findmax(int s)
	{
		int rt = 0,ans = 0;
		down(i,31,0)
		{
			int b = (s >> i) & 1;
			if(son[rt][b^1]) rt = son[rt][b^1],ans+=(1<<i);
			else rt = son[rt][b];
		}
		return ans;
	}
	inline void init()
	{
		memset(son,0,sizeof son);
		memset(end,0,sizeof end);
		tot = 0;
	}
}t;
int n,a[N];
int now,lmax[N],rmax[N];
int main()
{
	io >> n;
	up(i,1,n) io >> a[i];
	t.insert(0);
	up(i,1,n)
	{
		now ^= a[i];//异或前缀和 
		t.insert(now);
		lmax[i] = max(lmax[i-1],t.findmax(now));//lmax表示i为右区间的最大异或区间和
		//当前前缀与前面的前缀 做最大异或和 
	}
	now = 0;
	t.init();
	t.insert(0);
	down(i,n,1)
	{
		now ^= a[i];
		t.insert(now);
		rmax[i] = max(rmax[i+1],t.findmax(now));
	}
	int ans = 0;
	up(i,1,n)
		ans = max(ans,lmax[i] + rmax[i+1]);
	io << ans;
	return 0;
}
