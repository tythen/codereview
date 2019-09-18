#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define re register
#define ll long long

#define up(i,a,b) for(register int i=a;i<=b;i++) 
#define down(i,a,b) for(register int i=a;i>=b;i--) 
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
const int N = 3e6+5;
int lg[N];
ll a[N];
struct st_list{
	ll stmax[20][N],stmin[20][N];
	inline void build(int n){
		lg[0]=-1;
		up(i,1,n) lg[i] = lg[i>>1] + 1, stmax[0][i] = stmin[0][i] = a[i];
		up(i,1,lg[n]) up(j,1,n-(1<<(i-1))) stmax[i][j] = max(stmax[i-1][j],stmax[i-1][j+(1<<(i-1))]),stmin[i][j] = min(stmin[i-1][j],stmin[i-1][j+(1<<(i-1))]);
	}
	inline ll queryans(int l,int r){
		int k = lg[r-l+1];
		return max(stmax[k][l], stmax[k][r-(1<<k)+1]) - min(stmin[k][l], stmin[k][r-(1<<k)+1]);
	}
}rmq;
int n,m;
int x,y,k;
int main(){
	io >> n >> m;
	up(i,1,n) io >> a[i];
	rmq.build(n);
	while(m--){
		io >> x >> y;
		io << rmq.queryans(x,y) << '\n';
	}
	return 0;
}

