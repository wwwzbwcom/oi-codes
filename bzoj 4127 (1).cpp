#include<algorithm>
#include<cstdio>
//#include<iostream>
#include<cstring>
using namespace std;
const int maxn=100100;
int wei[maxn];
int idx[maxn];
struct XDS
{
    struct Node
    {
        int ls,rs;
        int le,re;
        int val;
        long long fma;
        long long fsu,zsu;
        int fcn,zcn;
        long long add;
    }n[maxn*2];
    int nn;
    void push(int u)
    {
    	if(n[u].ls!=0)
    	{
    		n[n[u].ls].add+=n[u].add;
    		n[n[u].rs].add+=n[u].add;
    		n[u].add=0;
    		pull(u);
		}
		else
		{
			n[u].val+=n[u].add;
			n[u].add=0;
			if(n[u].val>=0)	n[u].zsu=n[u].val,n[u].zcn=1,n[u].fsu=0,n[u].fcn=0,n[u].fma=-1e18;
			else	n[u].fsu=-n[u].val,n[u].fcn=1,n[u].zsu=0,n[u].zcn=0,n[u].fma=n[u].val;
		}
    }
    void pull(int u)
    {
    	if(n[u].ls!=0)
    	{
    		n[u].fma=max(n[n[u].ls].fma+n[n[u].ls].add,n[n[u].rs].fma+n[n[u].rs].add);
    		n[u].zcn=n[n[u].ls].zcn+n[n[u].rs].zcn;
    		n[u].fcn=n[n[u].ls].fcn+n[n[u].rs].fcn;
    		n[u].zsu=n[n[u].ls].zsu+n[n[u].ls].add*n[n[u].ls].zcn+n[n[u].rs].zsu+n[n[u].rs].add*n[n[u].rs].zcn;
    		n[u].fsu=n[n[u].ls].fsu-n[n[u].ls].add*n[n[u].ls].fcn+n[n[u].rs].fsu-n[n[u].rs].add*n[n[u].rs].fcn;
		}
		else
		{
			n[u].val+=n[u].add;
			n[u].add=0;
			if(n[u].val>=0)	n[u].zsu=n[u].val,n[u].zcn=1,n[u].fsu=0,n[u].fcn=0,n[u].fma=-1e18;
			else	n[u].fsu=-n[u].val,n[u].fcn=1,n[u].zsu=0,n[u].zcn=0,n[u].fma=n[u].val;
		}
    }
    int build(int le,int re)
    {
        int u=++nn;
        n[u].le=le; n[u].re=re;
        if(le==re)
        {
        	n[u].ls=n[u].rs=0;
        	n[u].add=0;
        	n[u].val=wei[idx[le]];
        	if(n[u].val>=0)	n[u].zsu=n[u].val,n[u].zcn=1,n[u].fsu=0,n[u].fcn=0,n[u].fma=-1e18;
			else	n[u].fsu=-n[u].val,n[u].fcn=1,n[u].zsu=0,n[u].zcn=0,n[u].fma=n[u].val;
        }
        else
        {
            int mid=(le+re)/2;
            n[u].ls=build(le,mid);
            n[u].rs=build(mid+1,re);
            pull(u);
        } 
        return u;
    }
    void rangeadd(int u,int lc,int rc,int val)
    {
        if(lc>rc)    swap(lc,rc);
        int le=n[u].le,re=n[u].re;
        int mid=(le+re)/2;
        if(le==lc&&re==rc)
        {
			if(n[u].fma+n[u].add+val>=0&&le!=re)	push(u),rangeadd(n[u].ls,lc,mid,val),rangeadd(n[u].rs,mid+1,rc,val);
			else
			{
				n[u].add+=val;
				if(le==re)
				{
					n[u].val+=n[u].add;	n[u].add=0;
					if(n[u].val>=0)	n[u].zsu=n[u].val,n[u].zcn=1,n[u].fsu=0,n[u].fcn=0,n[u].fma=-1e18;
					else	n[u].fsu=-n[u].val,n[u].fcn=1,n[u].zsu=0,n[u].zcn=0,n[u].fma=n[u].val;
				}
			}
        }
        else
        {
            push(u);
            if(rc<=mid)  rangeadd(n[u].ls,lc,rc,val);
            else
            {
                if(lc>=mid+1)    rangeadd(n[u].rs,lc,rc,val);
                else    rangeadd(n[u].ls,lc,mid,val),rangeadd(n[u].rs,mid+1,rc,val);
            }
            pull(u);
        }
    }
    long long rangesum(int u,int lc,int rc)
    {
        if(lc>rc)    swap(lc,rc);
        int le=n[u].le,re=n[u].re;
        int mid=(le+re)/2;
        if(le==lc&&re==rc)	return n[u].zsu+n[u].add*n[u].zcn+n[u].fsu-n[u].add*n[u].fcn;
		else
        {
            push(u);
            long long ans=0;
            if(rc<=mid)  ans=rangesum(n[u].ls,lc,rc);
            else
            {
                if(lc>=mid+1)    ans=rangesum(n[u].rs,lc,rc);
                else    ans=rangesum(n[u].ls,lc,mid)+rangesum(n[u].rs,mid+1,rc);
            }
            pull(u);
            return ans;
        }
    }
}xds;
struct  LCT
{
    struct Edge
    {
        int v,nxt;
    }e[maxn*2];
    int pre[maxn],en;
    LCT()
    {
        memset(pre,-1,sizeof pre);
        en=0;
    }
    int n;
    int lev[maxn],cnt[maxn];
    int fat[maxn],bfa[maxn],pos[maxn],pc;
    void addedge(int u,int v)
    {
        e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
        e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
    }
    void prebuild(int u,int f,int l)
    {
        lev[u]=l;
        for(int i=pre[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v;
            if(v!=f)
            {
                prebuild(v,u,l+1);
                cnt[u]+=cnt[v];
            }
        }
        cnt[u]++;
    }
    void build(int u,int f,int bf,int l)
    {
        fat[u]=f;   bfa[u]=bf;  pos[u]=++pc;    idx[pc]=u;  lev[u]=l;
        for(int i=pre[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v;
            if(v!=f&&cnt[v]>cnt[u]/2)   build(v,u,bf,l);
        }
        for(int i=pre[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v;
            if(v!=f&&cnt[v]<=cnt[u]/2)    build(v,u,v,l+1);
        }
    }
    void add(int u,int v,int val)
    {
        while(1)
        {
            if(bfa[u]==bfa[v])
            {
                xds.rangeadd(1,pos[u],pos[v],val);
                break;
            }
            else
            {
                if(lev[u]>lev[v])    xds.rangeadd(1,pos[u],pos[bfa[u]],val),u=fat[bfa[u]];
                else    xds.rangeadd(1,pos[v],pos[bfa[v]],val),v=fat[bfa[v]];
            }
        }
    }
    long long sum(int u,int v)
    {
        long long ans=0;
        while(1)
        {
            if(bfa[u]==bfa[v])  
            {
                ans+=xds.rangesum(1,pos[u],pos[v]);
                break;
            }
            else
            {
                if(lev[u]>lev[v])    ans+=xds.rangesum(1,pos[u],pos[bfa[u]]),u=fat[bfa[u]];
                else    ans+=xds.rangesum(1,pos[v],pos[bfa[v]]),v=fat[bfa[v]];
            }
        }
        return ans;
    }
     
}lct;
 
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    lct.n=n;
    for(int i=1;i<=n;i++)    scanf("%d",&wei[i]);
    for(int i=1;i<=n-1;i++)
    {
        int u,v;    scanf("%d%d",&u,&v);
        lct.addedge(u,v);
    }
    lct.prebuild(1,0,1);
    lct.build(1,0,1,1);
    xds.build(1,n);
    for(int i=1;i<=m;i++)
    {
        int cmd,u,v,val;    scanf("%d",&cmd);
        if(cmd==1)  scanf("%d%d%d",&u,&v,&val),lct.add(u,v,val);
        if(cmd==2)  scanf("%d%d",&u,&v),printf("%lld\n",lct.sum(u,v));
    }
}

