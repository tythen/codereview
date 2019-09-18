#include<iostream>
#include<cstdio>
#include<cmath>
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
	inline int rd(){
		int x;*this >> x;return x;
	}
}io;
const int N = 3e5+5;
struct edge{int v,nxt;}e[N];
int h[N],tot;
inline void add(int x,int y){
	e[++tot] = (edge){y,h[x]};
	h[x] = tot;
}
int dp[N][3],w[N];
inline void dfs(int x,int f)
{
	int sum=0;dp[x][1] = w[x];
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;
		dfs(v,x);
		dp[x][0] += min(dp[v][1],dp[v][2]);//���λ���ɸ��׷ţ�����Ҫô�Լ��ţ�Ҫô���ӵĶ��ӷ�
		dp[x][1] += min(min(dp[v][0],dp[v][1]),dp[v][2]);//�Լ����ˣ�����������һ�����ת�ƶ���
		sum += min(dp[v][1],dp[v][2]);//�ȼ������ж��Ӷ����ɵ���� 
	}
	dp[x][2] = 0x7f7f7f7f;
	Auto(i,x)
	{
		int v = e[i].v;
		if(v==f) continue;//���Ǳ���ץһ��������ǿ�з�һ������֤�Լ��ɶ��Ӹ��� 
		dp[x][2] = min(dp[x][2],sum - min(dp[v][1],dp[v][2]) + dp[v][1]);//��Ȼ������ѡ��С�� 
	}	
}
int a,b,c;
int n;
int main()
{
	io >> n;
	up(i,1,n)
	{
		io >> a;io >> w[a];io >> c;
		while(c--){io >> b;add(a,b),add(b,a);}
	}
	dfs(1,0);
	io << min(dp[1][1],dp[1][2]);
	return 0;
}
