#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
#define re register
#define mid ((l+r) >>1)

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
const int N = 1e3+5;
/*
贪心策略：尽量让1号机器的空闲更少，但是同时2号机器空闲尽量少
让1号机器处理时间短的，同时让2号机器处理时间长的 
起决定作用的是a，b中最小的 
先按（a，b）排序 
*/
int n;
struct node{
	int a,b,s,id;
	friend bool operator < (const node a,const node b){
		return a.s < b.s;
	}
}q[N],q2[N];
int ans[N];
int main(){
	io >> n;
	for(int i=1;i<=n;i++) io >> q[i].a;
	for(int i=1;i<=n;i++) io >> q[i].b;
	for(int i=1;i<=n;i++){
		q[i].id = i;
		q[i].s = min(q[i].a,q[i].b);
		q2[i] = q[i];
	}
	sort(q+1,q+1+n);
//	for(int i=1;i<=n;i++) printf("%d(%d) ",q[i].id,q[i].s);
	for(int i=1,l=1,r=n;i<=n;i++){
		if(q[i].a == q[i].s) ans[l++] = q[i].id;
		else ans[r--] = q[i].id;
	}
	int ta = 0, tb = 0;
	for(int i=1;i<=n;i++) {
		int k = ans[i];
		ta += q2[k].a;
		if(tb < ta) tb = ta;
		tb += q2[k].b;
	}
	io << tb << '\n';
	for(int i=1;i<n;i++) io << ans[i] << ' '; 
	io << ans[n];
	return 0;
}
