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
const int N = 1e3+5;
/*
我们尝试转换状态空间的结构和遍历方式
从结果上说，对于每一个“钓过的鱼塘 ”，我们花费了时间去到达，也钓过了鱼，但先后顺序是等价的，
在花过时间走过了每一个 “钓过的鱼塘 ”之后，就可以视作我们同时出现在每一个鱼塘，可以任意钓最优的鱼
那么问题转化成了找最远的“钓过的鱼塘”这一点我反而想了半天，结果艹直接枚举这个东西然后重复算法不就得了
给我一个启示，在高水平思维过程之后要回归状态空间理论的本质：遍历！ 
*/ 
int n; 
struct node{
	int fish,id,d;
	friend bool operator < (const node a,const node b){
		return a.fish < b.fish;
	}	
}a[N];
priority_queue <node> q; 
int t,dis[N];
int main(){
	io >> n;
	io >> t;
	t *= 12;//以5分钟为单位，1小时有12个 
	for(int i=1;i<=n;i++) io >> a[i].fish,a[i].id = i;
	for(int i=1;i<=n;i++) io >> a[i].d;
	for(int i=1;i<n;i++) io >> dis[i];
	int nt = t,ans = 0; 
	for(int i=1;i<=n;i++){//现在最远的是第i个鱼塘 
		int T = nt;//这个T是已经减去路程的 
		int tmpans = 0;
		while(!q.empty()) q.pop();
		if(T < 0) break;//艹！ 
		for(int j=1;j<=i;j++) q.push(a[j]);
		while(T){
			node b = q.top();q.pop();
			tmpans += b.fish;
			b.fish -= b.d;
			if(b.fish<0) b.fish = 0; //艹！ 
			q.push(b);
			T--;
		}
		
		ans = max(ans,tmpans);
		nt -= dis[i];
	}
	io << ans;
	return 0;
}
