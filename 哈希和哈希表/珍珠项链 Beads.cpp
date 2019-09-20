#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define up(i,a,b) for(register int i=a;i<=b;i++) 
#define re register
using namespace std;
struct ios{
	template <typename ty> inline ios& operator >> (ty &x)
	{
		x= 0;int f = 1;register char c=getchar();
		for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
		for(;isdigit(c);c=getchar()) x = (x<<1) + (x<<3) + (c^48);
		x*=f;return *this;
	}
	template <typename ty> inline ios& operator << (ty x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) *this << x/10;
		putchar(x%10+48);return *this;
	}
	inline ios& operator << (char x){putchar(x);return *this;}
}io;
const int N = 4e6+5;
const int p = 199993;
const int p2 = 199993;
ull power[N];
struct hash_function{
	ull H[N];
	inline void init(int *s,int len){
		up(i,1,len) H[i] = H[i-1] * p + s[i];
	}
	inline ull hash(int l,int r){
		return H[r] - H[l-1] * power[r-l+1];
	}
}a,b;
//map <ull,int> ha;//stl写clear就没问题 
struct hash_table{
	struct node{ull key;int val,nxt;}e[N<<1];
	int h[N],tot;
	inline int& operator [] (const ull key){
		for(int i=h[key%p2];i;i=e[i].nxt){
			if(e[i].key == key) return e[i].val;
		}
		e[++tot] = (node){key,0,h[key%p2]};
		h[key%p2] = tot;
		return e[tot].val;
	}
	inline void clear()
	{
		for(int i=0;i<=tot*2;++i) h[i] = 0;
		tot = 0;
	}
}ha;
int n;
int arr[N],vis[N];
int ans,ans2[N];
int main()
{
	power[0] = 1;up(i,1,2e5) power[i] = power[i-1] * p;
	io >> n;
	up(i,1,n) io >> arr[i];
	a.init(arr,n);
	reverse(arr+1,arr+1+n);
	b.init(arr,n);
	for(int k=1;k<=n;k++)
	{
		if(n / k < ans) break;
//		ha.clear();//真他妈绝了，手写hash因为每次clear被卡了  这个题不用clear的，因为不同长度没有完全一样的串 
		int cnt = 0;
		for(int l=1;1;l+=k)
		{
			int r = l+k-1;
			if(r>n) break;
			int *h1,*h2;
			h1 = &ha[a.hash(l,r)],h2 = &ha[b.hash(n-r+1,n-l+1)];
			if((*h1==0) && (*h2==0))
			{
				*h1 = *h2 = 1;
				cnt++;
			}
		}
		ans = max(ans,cnt);
		vis[k] = cnt;
	}
	up(i,1,n){
		if(vis[i] == ans) ans2[++ans2[0]] = i;
	}
	io << ans << ' ' << ans2[0] << '\n';
	up(i,1,ans2[0]) io << ans2[i] << ' ';
	return 0;
}

