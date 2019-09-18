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
贪心策略：优先队列完了 
*/
priority_queue <int,vector<int>,greater<int> > maxx;
priority_queue <int> minn;
int n,tp,tp2;
int main(){
	io >> n;
	for(int i=1;i<=n;i++){
		io >> tp;
		maxx.push(tp);
		minn.push(tp);
	}
	for(int i=1;i<n;i++){
		tp = maxx.top();maxx.pop();
		tp2 = maxx.top();maxx.pop();
//		printf("maxx:%d,%d -> %d     ",tp,tp2,tp*tp2+1);
		maxx.push(tp*tp2 + 1);
		tp = minn.top();minn.pop();
		tp2 = minn.top();minn.pop();
//		printf("minn:%d,%d -> %d\n",tp,tp2,tp*tp2+1);
		minn.push(tp*tp2 + 1);		
	}
	io << maxx.top() - minn.top();
	return 0;
}
