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
const int N = 5e6+5; 
const int p = 133337;
struct hash_table{
	struct node{
		int key;
		int val,nxt;
	}e[N];
	int h[N],tot;
	inline int& operator [] (const int key)
	{
		for(int i=h[key%p];i;i=e[i].nxt) if(e[i].key == key) return e[i].val;
		e[++tot] = (node){key,0,h[key%p]};
		h[key%p] = tot;
		return e[tot].val;
	}
	inline void clear()
	{
		for(int i=0;i<=tot;i++) h[i] = 0,e[i].key = e[i].nxt = e[i].val = 0;
		tot = 0;
	}
}ha;
int T,n;
int a[N],ans;
int main()
{
//	freopen("snow0.in","r",stdin);
	io >> n;
	up(i,1,n) io >> a[i];
	int l = 1,r = 0;
	for(int i=1;i<=n;i++)
	{
		if(ha[a[i]] == 0) ha[a[i]]++,r++;
		else
		{
			while(l<=n && a[l]!=a[i])
			{
				ha[a[l]]--;
				l++;
			}
			ha[a[l]]--;
			l++;
			ha[a[i]]++;
			r++;
		}
		ans = max(ans,r-l+1);
	}
	io << ans;
	return 0;
}
