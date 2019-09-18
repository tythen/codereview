#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long 
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
struct st_list{
	int st[20][N];//Çómax 
	inline void bulid(int *a,int len){
		for(register int i=1;i<=len;i++) st[0][i] = a[i],lg[i] = (i>=2)?(lg[i>>1]+1):0;
		for(register int i=1;i<=lg[len]+1;i++)
			for(register int j=1;j<=len;j++)
				st[i][j] = max(st[i-1][j],st[i-1][j+(1<<(i-1))]);//(j,j+2^(i-1)-1) - (j+2^(i-1),j+2^i-1)
	}
	inline int query(int l,int r){
		int k = lg[r-l+1];
		return max(st[k][l],st[k][r-(1<<k)+1]);//pos+2^k-1 = r
	}
}rmq;
int n,m;
int a[N],x,y;
int main(){
	io >> n >> m;
	for(register int i=1;i<=n;i++) io >> a[i];
	rmq.bulid(a,n);
	while(m--){
		io >> x >> y;
		io << rmq.query(x,y) << '\n';
	}
	return 0;
}

