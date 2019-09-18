#include <bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
int n,q,w[maxn],c[maxn],T[maxn],sz;
int head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int dep[maxn],top[maxn],son[maxn],siz[maxn],fa[maxn],id[maxn],mp[maxn],tim;
struct node{
    int lson,rson,val,sum;
    #define mid (l+r>>1)
    #define lson(rt) tree[rt].lson
    #define rson(rt) tree[rt].rson
    #define val(rt) tree[rt].val
    #define sum(rt) tree[rt].sum
}tree[maxn*24];

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}
inline void add(int x,int y){//����
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}

void dfs1(int x,int f){//������ȡ��ض��ӡ�������С�͸���
    dep[x]=dep[f]+1;
    siz[x]=1;
    fa[x]=f;
    int maxson=-1;
    for(int i=head[x],y;i;i=nxt[i]){
        y=to[i];
        if(y==f) continue;
        dfs1(y,x);
        siz[x]+=siz[y];
        if(maxson<siz[y]){
            maxson=siz[y];
            son[x]=y;
        }
    }
}

void dfs2(int x,int topf){//�����������
    id[x]=++tim;
    mp[tim]=x;
    top[x]=topf;
    if(son[x]) dfs2(son[x],topf);
    for(int i=head[x],y;i;i=nxt[i]){
        y=to[i];
        if(y==fa[x]||y==son[x]) continue;
        dfs2(y,y);//����дdfs2(y,x)!
    }
}

void pushup(int rt){//�ϴ�����
    val(rt)=max(val(lson(rt)),val(rson(rt)));
    sum(rt)=sum(lson(rt))+sum(rson(rt));
}
void pushdown(int rt){//ɾ�����
    val(rt)=sum(rt)=0;
}
void update(int &rt,int x,int l,int r,int v){//��̬����
    if(!rt) rt=++sz;
    if(l == r){
        val(rt)=sum(rt)=v;
        return ;
    }
    if(x <= mid) update(lson(rt),x,l,mid,v);
    else update(rson(rt),x,mid+1,r,v);
    pushup(rt);
}
void del(int &rt,int x,int l,int r){//ɾ�����
    if(!rt) return ;//��֦
    if(l == r){
        pushdown(rt);
        return ;
    }
    if(x <= mid) del(lson(rt),x,l,mid);
    else del(rson(rt),x,mid+1,r);
    pushup(rt);
}
int query_sum(int &rt,int L,int R,int l,int r){//��ѯ�����
    if(!rt) return 0;
    if(L <= l && r <= R){
        return sum(rt);
    }
    int ans=0;
    if(L <= mid) ans+=query_sum(lson(rt),L,R,l,mid);
    if(R > mid) ans+=query_sum(rson(rt),L,R,mid+1,r);//����дelse! 
    return ans;
}
int query_max(int &rt,int L,int R,int l,int r){//��ѯ�������ֵ
    if(!rt) return 0;
    if(L <= l && r <= R){
        return val(rt);
    }
    int ans=0;
    if(L <= mid) ans=max(ans,query_max(lson(rt),L,R,l,mid));
    if(R > mid) ans=max(ans,query_max(rson(rt),L,R,mid+1,r));//����дelse! 
    return ans;
}

int main()
{
	freopen("q20.in","r",stdin);
	freopen("std.out","w",stdout);
    n=read(),q=read();int x,y,k,ans;
    for(int i=1;i<=n;i++)
        w[i]=read(),c[i]=read();
    for(int i=1;i<n;i++){
        x=read(),y=read();
        add(x,y);add(y,x);
    }
    dfs1(1,0);dfs2(1,1);
    for(int i=1;i<=n;i++)//Ԥ����
        update(T[c[mp[i]]],i,1,n,w[mp[i]]);
    char opt[50];
    while(q--){
        scanf("%s",opt);
        if(opt[1]=='C'){//�����ڽ�
            x=read(),k=read();
//            del(T[c[x]],id[x],1,n);
//            c[x]=k;
//            update(T[c[x]],id[x],1,n,w[x]);
        }
        if(opt[1]=='W'){//��������
            x=read(),k=read();
//            del(T[c[x]],id[x],1,n);
//            w[x]=k;
//            update(T[c[x]],id[x],1,n,w[x]);
        }
        if(opt[1]=='S'){//�������
            x=read(),y=read();
            k=c[x];ans=0;
            while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]]) swap(x,y);//����дdep[x]<dep[y]!
                ans+=query_sum(T[k],id[top[x]],id[x],1,n);
                x=fa[top[x]];
            }
            if(dep[x]>dep[y]) swap(x,y);
            ans+=query_sum(T[k],id[x],id[y],1,n);
            printf("%d\n",ans);
        }
        if(opt[1]=='M'){//���������ֵ
            x=read(),y=read();
            k=c[x];ans=0;
//            while(top[x]!=top[y]){
//                if(dep[top[x]]<dep[top[y]]) swap(x,y);//����дdep[x]<dep[y]!
//                ans=max(ans,query_max(T[k],id[top[x]],id[x],1,n));
//                x=fa[top[x]];
//            }
//            if(dep[x]>dep[y]) swap(x,y);
//            ans=max(ans,query_max(T[k],id[x],id[y],1,n));
            printf("%d\n",ans);
        }
    }
    for(int i=1;i<=n;i++) cout << T[i] << ' ';
    printf("tot = %d",sz); 
    return 0;
}
