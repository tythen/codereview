#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
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
int vis[N];
struct Trie{
	int son[N][2],tot,end[N],ontrie[N];
	inline void insert(int *s,int len)
	{
		int rt = 0;
		up(i,0,len-1)
		{
			int v = s[i];
			if(!son[rt][v]) son[rt][v] = ++tot;
			rt = son[rt][v];
			ontrie[rt] ++;
		}
		end[rt]++;
	}
	inline int query(int *s,int len)
	{
		int rt = 0,ans = 0;
		up(i,0,len-1)
		{
			int v = s[i];
			if(!son[rt][v]) return ans;
			rt = son[rt][v];
			if(end[rt]) ans+=end[rt];
		}
		ans += ontrie[rt];
		if(end[rt]) return ans -= end[rt];//减去多余 
		return ans;
	}
}t;
int n,m;//可能密码是信息的前缀，也可能信息是密码的前缀
//在查询串结束时(ontrie)，在遇到end时 
int d,a[N];
int main()
{
	io >> n >> m;
	while(n--)
	{
		io >> d;
		up(i,0,d-1) io >> a[i];
		t.insert(a,d); 
	}
	while(m--)
	{
		io >> d;
		up(i,0,d-1) io >> a[i];
		io << t.query(a,d) <<'\n'; 
	}	
	return 0;
}


