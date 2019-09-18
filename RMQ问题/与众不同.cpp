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
/*
首先我觉得这个题不能算rmq是重点，重点是这个区间最大不重复子串长度的模型
最大不重复子串：他的子串也一定是不重复子串，我们要利用这个 
我们首先有简化模型：整个序列最大不重复子串长度：
start[i]表示i结尾 的最长不重复子串 的开头位置，用last[]表示上一个元素出现的位置 
start[i] = max(start[i-1], last[a[i]]+1)
dp[i]表示i结尾的最长不重复子串 dp[i] = i-start[i]+1
显然start[i] 具有单调性：想到用二分求一个在 lr之间的值mid，使start[i]<l(i<mid) start[i]>=l(i>=mid)
左边的用dp算一下就可以了，而右边用rmq求最大dp 
*/
int lg[N];
struct st_list{
	int st[20][N];
	inline void build(int n,int *a){
		lg[0] = -1;
		up(i,1,n) lg[i] = lg[i>>1] + 1,st[0][i] = a[i];
		up(i,1,lg[n]) up(j,1,n-(1<<(i-1))) st[i][j] = max(st[i-1][j],st[i-1][j + (1<<(i-1))]);
	}
	inline int query(int l,int r){
		int k = lg[r-l+1];
		return max(st[k][l], st[k][r-(1<<k)+1]);
	}
}rmq;
int n,m;
int x,y;
const int L = 1e6;//它有负数好阴哟 
int a[N];
int last[N],dp[N],start[N];
inline int sovle(int l,int r){
	if(start[l] >= l) return rmq.query(l,r);
	int k = l,le = l,ri = r;
	while(le <= ri){
		int mid = (le+ri) >> 1;
		if(start[mid] < l) le = mid+1; //找尽量靠后的位置
		else ri  = mid-1;
	}
	int ans = 0;
	if(le>l) ans = le-l;
	if(le <= r) ans = max(ans,rmq.query(le,r));
	return ans;
}
int main(){
	io >> n >> m;
	up(i,1,n) io >> a[i];
	up(i,1,n){
		start[i] = max(start[i-1], last[a[i] + L]+1);//保证合法 
		dp[i] = i-start[i]+1; 
		last[a[i] + L] = i;
	}
	rmq.build(n,dp);
	while(m--){
		io >> x >> y;
		io << sovle(++x,++y) << '\n';
	}
	return 0;
}


