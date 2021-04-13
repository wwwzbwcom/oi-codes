#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1010;
struct intree
{
    struct Node
    {
        int ls,rs;
        int val,mxa;
    }n[maxn*2];
    int nn;
    int build(int le,int re)
    {
        int u=++nn;
        n[u].val=n[u].mxa=0;
        if(le==re)  return u;
        else
        {
            int mid=(le+re)/2;
            n[u].ls=build(le,mid);
            n[u].rs=build(mid+1,re);
        }
        return u;
    }
    void rangeset(int u,int le,int re,int lc,int rc,int val)
    {
        int ls=n[u].ls,rs=n[u].rs;
        int mid=(le+re)/2;
        n[u].mxa=max(n[u].mxa,val);
        if(le==lc&&re==rc)
        {
            n[u].val=max(n[u].val,val);
            return;
        }
        else
        {
            if(rc<=mid)  rangeset(ls,le,mid,lc,rc,val);
            else
            {
                if(lc>=mid+1)    rangeset(rs,mid+1,re,lc,rc,val);
                else    rangeset(ls,le,mid,lc,mid,val),rangeset(rs,mid+1,re,mid+1,rc,val);
            }
        }
    }
    int rangemax(int u,int le,int re,int lc,int rc)
    {
        int ls=n[u].ls,rs=n[u].rs;
        int mid=(le+re)/2;
        if(le==lc&&re==rc)  return n[u].mxa;
        else
        {
            int ans=0;
            if(rc<=mid)  ans=rangemax(ls,le,mid,lc,rc);
            else
            {
                if(lc>=mid+1)    ans=rangemax(rs,mid+1,re,lc,rc);
                else    ans=max(rangemax(ls,le,mid,lc,mid),rangemax(rs,mid+1,re,mid+1,rc));
            }
            ans=max(ans,n[u].val);
            return ans;
        }
    }
};
struct outree
{
    struct Node
    {
        int le,re;
        int ls,rs;
        intree val,mxa;
    }n[maxn*2];
    int nn;
    int len;
    int build(int le,int re)
    {
        int u=++nn;
        n[u].le=le; n[u].re=re;
        n[u].val.build(1,len);
        n[u].mxa.build(1,len);
        if(le==re)  return u;
        else
        {
            int mid=(le+re)/2;
            n[u].ls=build(le,mid);
            n[u].rs=build(mid+1,re);
        }
        return u;
    }
    void rangeset(int u,int lc,int rc,int ilc,int irc,int val)
    {
        int ls=n[u].ls,rs=n[u].rs;
        int le=n[u].le,re=n[u].re;
        int mid=(le+re)/2;
        n[u].mxa.rangeset(1,1,len,ilc,irc,val);
        if(le==lc&&re==rc)  n[u].val.rangeset(1,1,len,ilc,irc,val);
        else
        {
             
            if(rc<=mid)  rangeset(ls,lc,rc,ilc,irc,val);
            else
            {
                if(lc>=mid+1)    rangeset(rs,lc,rc,ilc,irc,val);
                else    rangeset(ls,lc,mid,ilc,irc,val),rangeset(rs,mid+1,rc,ilc,irc,val);
            }
        }
    }
    int rangemax(int u,int lc,int rc,int ilc,int irc)
    {
        int ls=n[u].ls,rs=n[u].rs;
        int le=n[u].le,re=n[u].re;
        int mid=(le+re)/2;
        if(le==lc&&re==rc)  return n[u].mxa.rangemax(1,1,len,ilc,irc);
        else
        {
            int ans=0;
            if(rc<=mid)  ans=rangemax(ls,lc,rc,ilc,irc);
            else
            {
                if(lc>=mid+1)    ans=rangemax(rs,lc,rc,ilc,irc);
                else    ans=max(rangemax(ls,lc,mid,ilc,irc),rangemax(rs,mid+1,rc,ilc,irc));
            }
            ans=max(ans,n[u].val.rangemax(1,1,len,ilc,irc));
            return ans;
        }
    }
}ot;
int main()
{
    int x,y,n;  scanf("%d%d%d",&x,&y,&n);
    ot.len=x;
    ot.build(1,y);
    for(int i=1;i<=n;i++)
    {
        int xl,yl,h,xp,yp;  scanf("%d%d%d%d%d",&xl,&yl,&h,&xp,&yp);
        int mxa=ot.rangemax(1,yp+1,yp+yl,xp+1,xp+xl);
        ot.rangeset(1,yp+1,yp+yl,xp+1,xp+xl,mxa+h);
    }
    printf("%d",ot.rangemax(1,1,y,1,x));
     
}
