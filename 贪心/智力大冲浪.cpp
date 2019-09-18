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
贪心策略：在尽量早的时间完成当前能完成的扣分最大的游戏
把最大的分值的优先加入处理时间序列vis中，尽量在时间轴上靠后放置
如果放不下来的游戏只有扣分了 
*/
int n;
struct node{
	int t,soc;
	friend bool operator < (const node a,const node b){
		return a.soc > b.soc;
	}
}a[505];
int money;
int vis[505];
int main(){
	io >> money >> n;
	for(int i=1;i<=n;i++) io >> a[i].t;
	for(int i=1;i<=n;i++) io >> a[i].soc;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		int pos;
		for(pos = a[i].t;pos;pos--){
			if(vis[pos]==0){
				vis[pos] = i;
				break;
			}
		}
		if(!pos) money -= a[i].soc;
	}
	io << money;
	return 0;
}
