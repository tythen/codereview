#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
#define re register

using namespace std;
struct ios{
	inline char fchar(){
		static char buf[100000],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
	}
//	#define getchar fchar
	template <typename ty> inline ios& operator >> (ty &x)
	{
		register int f=1;x=0;register char c=getchar();
		for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
		for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
		x*=f;return *this;
	}
	template <typename ty>  inline ios& operator << (ty x)
	{
		if(x<0) x=-x,putchar('-');
		if(x>9) *this << x/10;
		putchar(x%10+48);
		return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
/*
区间选点问题 
按结束位置排序 
尽量在靠后的位置种树 
*/ 
const int N = 3e5+5;
int n,m;

struct node{
	int l,r,need;
}a[N];
int vis[N];
inline bool cmp(node x,node y){
	return x.r < y.r;
}

int main(){
	io >> n >> m;
	for(int i=1;i<=m;i++) io >> a[i].l >> a[i].r >> a[i].need;
	
	sort(a+1,a+1+m,cmp);
	
	ll ans = 0;
	for(int i=1;i<=m;i++){
		int flag = 0;
		for(int j=a[i].l; j<=a[i].r; j++) 
		{
			if(vis[j]) a[i].need--;
			if(a[i].need <= 0) {
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		for(int j=a[i].r;j>=a[i].l;j--)
		{
			if(!vis[j] && a[i].need>0){//这里写>0啊我傻逼了 
				vis[j] = 1;
				ans++;
				a[i].need--;
				if(a[i].need <= 0) break;
			}
		}
	}
//	for(int i=1;i<=n;i++) io << vis[i] <<' ';
	io << ans;
	return 0;
} 
