#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>

#define ll long long
#define pau system("pause")
#define ull unsigned ll
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
}io;
const ll inf = 0x7f7f7f7f;
const int p = 13331;
const int N = 2e5+5;
/*
这个题有十分麻烦的转换方案，不搞错就可以了 
*/
struct stage{
	string a;
	string op;
};
string ed,st;
queue <stage> q;
int num;
map <string,int> vis;
int main()
{
	up(i,1,8) io >> num,ed.push_back(num+'0');
	up(i,1,8) st.push_back(i+'0');
	
	q.push((stage){st,""});
	vis[st] = 1;
	while(!q.empty())
	{
		string nows = q.front().a;
		string op = q.front().op;
		q.pop();
		if(nows == ed)
		{
			io << op.size() <<'\n';
			cout << op;
		}
		string s = "";
		s = nows;
		reverse(s.begin(),s.end());
		if(!vis[s]) 
		{
			q.push((stage){s,op+"A"});
			vis[s] = 1;
		}
		
		
		s = "";
		s += nows.substr(3,1);
		s += nows.substr(0,3);
		s += nows.substr(5,3);
		s += nows.substr(4,1);
		if(!vis[s]) 
		{
			q.push((stage){s,op+"B"});
			vis[s] = 1;
		}		
		
		s = nows;
		s[1] = nows[6],s[2] = nows[1], s[3] = nows[3];
		s[4] = nows[4],s[5] = nows[2], s[6] = nows[5];
		if(!vis[s]) 
		{
			q.push((stage){s,op+"C"});
			vis[s] = 1;
		}		
	}
	
	
	return 0;
}
