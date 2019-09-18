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
���ǳ���ת��״̬�ռ�Ľṹ�ͱ�����ʽ
�ӽ����˵������ÿһ�������������� �������ǻ�����ʱ��ȥ���Ҳ�������㣬���Ⱥ�˳���ǵȼ۵ģ�
�ڻ���ʱ���߹���ÿһ�� ������������ ��֮�󣬾Ϳ�����������ͬʱ������ÿһ��������������������ŵ���
��ô����ת����������Զ�ġ���������������һ���ҷ������˰��죬���ֱܳ��ö���������Ȼ���ظ��㷨���͵���
����һ����ʾ���ڸ�ˮƽ˼ά����֮��Ҫ�ع�״̬�ռ����۵ı��ʣ������� 
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
	t *= 12;//��5����Ϊ��λ��1Сʱ��12�� 
	for(int i=1;i<=n;i++) io >> a[i].fish,a[i].id = i;
	for(int i=1;i<=n;i++) io >> a[i].d;
	for(int i=1;i<n;i++) io >> dis[i];
	int nt = t,ans = 0; 
	for(int i=1;i<=n;i++){//������Զ���ǵ�i������ 
		int T = nt;//���T���Ѿ���ȥ·�̵� 
		int tmpans = 0;
		while(!q.empty()) q.pop();
		if(T < 0) break;//ܳ�� 
		for(int j=1;j<=i;j++) q.push(a[j]);
		while(T){
			node b = q.top();q.pop();
			tmpans += b.fish;
			b.fish -= b.d;
			if(b.fish<0) b.fish = 0; //ܳ�� 
			q.push(b);
			T--;
		}
		
		ans = max(ans,tmpans);
		nt -= dis[i];
	}
	io << ans;
	return 0;
}
