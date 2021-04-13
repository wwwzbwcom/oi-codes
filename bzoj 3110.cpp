#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=50100;
struct inNode
{
    int ls,rs;
    int add,sum;
}in[maxn*600];
int inn=0;
struct inTree
{
    int r;
    void pull(int u,int le,int re)
    {
        int ls=in[u].ls,rs=in[u].rs;
        int mid=(le+re)/2;
        if(ls!=0)   in[u].sum=in[ls].sum+in[ls].add*(mid-le+1)+in[rs].sum+in[rs].add*(re-(mid+1)+1);
    }
    void push(int u,int le,int re)
    {
        if(in[u].ls!=0)
        {
            in[in[u].ls].add+=in[u].add;
            in[in[u].rs].add+=in[u].add;
            in[u].add=0;
        }
    }
    int newnode()
    {
        int u=++inn;
        in[u].ls=in[u].rs=0;
        in[u].add=in[u].sum=0;
        return u;
    }
    void addval(int u,int le,int re,int lc,int rc,int val)
    {
        int mid=(le+re)/2;
        if(le!=re)
        {
            if(in[u].ls==0) in[u].ls=newnode();
            if(in[u].rs==0) in[u].rs=newnode();
        }
        int ls=in[u].ls,rs=in[u].rs;
             
        
        if(le==lc&&re==rc)
        {
            in[u].add+=val;
            return;
        }
		push(u,le,re);
        if(rc<=mid)  addval(ls,le,mid,lc,rc,val);
        else
        {
            if(lc>=mid+1)    addval(rs,mid+1,re,lc,rc,val);
            else    addval(ls,le,mid,lc,mid,val),addval(rs,mid+1,re,mid+1,rc,val);
        }
        pull(u,le,re);
    }
    int querysum(int u,int le,int re,int lc,int rc)
    {
        int mid=(le+re)/2;
        if(le!=re)
        {
            if(in[u].ls==0) in[u].ls=newnode();
            if(in[u].rs==0) in[u].rs=newnode();
        }
        int ls=in[u].ls,rs=in[u].rs;
        
        
        int ans=0;
        if(le==lc&&re==rc)
        {
            return in[u].sum+in[u].add*(re-le+1);
        }
        push(u,le,re);
        if(rc<=mid)  ans=querysum(ls,le,mid,lc,rc);
        else
        {
            if(lc>=mid+1)    ans=querysum(rs,mid+1,re,lc,rc);
            else    ans=querysum(ls,le,mid,lc,mid)+querysum(rs,mid+1,re,mid+1,rc);
        }
        pull(u,le,re);
        return ans;
    }
};
struct outTree
{
    struct outNode
    {
        int le,re;
        int ls,rs;
        inTree tre;
    }on[maxn*2];
    int onn;
    int build(int le,int re)
    {
        int mid=(le+re)/2;
        int u=++onn;
        on[u].le=le;on[u].re=re;
        on[u].tre.r=on[u].tre.newnode();
    //  getchar();
        if(le==re)  on[u].ls=on[u].rs=0;
        else
        {
            on[u].ls=build(le,mid);
            on[u].rs=build(mid+1,re);
        }
        return u;
    }
    void addrange(int u,int aim,int ilc,int irc)
    {
        int ls=on[u].ls,rs=on[u].rs;
        int le=on[u].le,re=on[u].re;
        int mid=(le+re)/2;
        on[u].tre.addval(on[u].tre.r,1,50000,ilc,irc,1);
        if(le==re)  return;
        if(aim<=mid) addrange(ls,aim,ilc,irc);
        else    addrange(rs,aim,ilc,irc);
         
    }
    int queryans(int u,int aim,int ilc,int irc)
    {
        int ls=on[u].ls,rs=on[u].rs;
        int le=on[u].le,re=on[u].re;
        int mid=(le+re)/2;
        if(le==re)  return le;
        int rnum=on[rs].tre.querysum(on[rs].tre.r,1,50000,ilc,irc);
        if(rnum<aim) return  queryans(ls,aim-rnum,ilc,irc);
        else    return  queryans(rs,aim,ilc,irc);
    }
}out;
int n,m;
int cmd[maxn],a[maxn],b[maxn],c[maxn];
int sto[maxn],sn;
int idx[maxn];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&cmd[i],&a[i],&b[i],&c[i]);
        if(cmd[i]==1)   sto[sn++]=c[i];
    }
    sort(sto,sto+sn);
    sn=unique(sto,sto+sn)-sto;
    for(int i=1;i<=m;i++)
        if(cmd[i]==1)
        {
            int t=c[i];
            c[i]=lower_bound(sto,sto+sn,c[i])-sto+1;
            idx[c[i]]=t;
        }
    out.build(1,50000);
    for(int i=1;i<=m;i++)
    {
        if(cmd[i]==1)   out.addrange(1,c[i],a[i],b[i]);
        else    printf("%d\n",idx[out.queryans(1,c[i],a[i],b[i])]);
    //  cout<<i<<"===="<<endl;
    }
}
