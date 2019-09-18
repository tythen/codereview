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
�����Ҿ�������ⲻ����rmq���ص㣬�ص��������������ظ��Ӵ����ȵ�ģ��
����ظ��Ӵ��������Ӵ�Ҳһ���ǲ��ظ��Ӵ�������Ҫ������� 
���������м�ģ�ͣ�������������ظ��Ӵ����ȣ�
start[i]��ʾi��β ������ظ��Ӵ� �Ŀ�ͷλ�ã���last[]��ʾ��һ��Ԫ�س��ֵ�λ�� 
start[i] = max(start[i-1], last[a[i]]+1)
dp[i]��ʾi��β������ظ��Ӵ� dp[i] = i-start[i]+1
��Ȼstart[i] ���е����ԣ��뵽�ö�����һ���� lr֮���ֵmid��ʹstart[i]<l(i<mid) start[i]>=l(i>=mid)
��ߵ���dp��һ�¾Ϳ����ˣ����ұ���rmq�����dp 
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
const int L = 1e6;//���и�������Ӵ 
int a[N];
int last[N],dp[N],start[N];
inline int sovle(int l,int r){
	if(start[l] >= l) return rmq.query(l,r);
	int k = l,le = l,ri = r;
	while(le <= ri){
		int mid = (le+ri) >> 1;
		if(start[mid] < l) le = mid+1; //�Ҿ��������λ��
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
		start[i] = max(start[i-1], last[a[i] + L]+1);//��֤�Ϸ� 
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


