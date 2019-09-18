#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
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
const int N = 1e6+5;
struct node{
	int l,r;
}a[N];
inline bool cmp(node a,node b){
	return a.r < b.r;
}
int n;
int ans;
int main(){
	io >> n;
	for(int i=1;i<=n;i++) io >> a[i].l >> a[i].r;
	sort(a+1,a+1+n,cmp);
	int now = 0;
	while(now<=n){
		int flag = 0;
		for(int i=now+1;i<=n;i++){
			if(a[i].l >= a[now].r){
				ans++;
				now = i;
				flag = 1;
				break;
			}
		}
		if(!flag) break;
	}
	io << ans;
	return 0;
}
