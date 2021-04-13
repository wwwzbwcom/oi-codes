#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000100;
int wei[maxn],idx[maxn];
struct XDS
{
	struct Node
	{
		int ls,rs;
		int re,le;
		long long sum,add;
	}n[maxn*2];
	int nn;
	void push(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		if(ls!=0)
		{
			n[ls].add+=n[u].add;
			n[rs].add+=n[u].add;
			n[u].add=0;
		}
		pull(u);
	}
	void pull(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(ls!=0)	n[u].sum=n[ls].sum+n[ls].add*(mid-le+1)+n[rs].sum+n[rs].add*(re-(mid+1)+1);
	}
	int build(int le,int re)
	{
		int u=++nn;
		n[u].le=le;	n[u].re=re;
		n[u].add=0;
		if(le==re)	n[u].sum=wei[idx[le]];
		else
		{
			n[u].sum=0;
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	void add(int u,int lc,int rc,int val)
	{
		if(lc>rc)	swap(lc,rc);
		int ls=n[u].ls,rs=n[u].rs;
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		
		if(le==lc&&re==rc)
		{
			n[u].add+=val;
			return;
		}
		else
		{
			push(u);
			if(rc<=mid)	add(ls,lc,rc,val);
			else
			{
				if(lc>=mid+1)	add(rs,lc,rc,val);
				else	add(ls,lc,mid,val),add(rs,mid+1,rc,val);
			}
			pull(u);
		}
	}
	long long sum(int u,int lc,int rc)
	{
		if(lc>rc)	swap(lc,rc);
		int ls=n[u].ls,rs=n[u].rs;
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		
		if(le==lc&&re==rc)	return	n[u].sum+n[u].add*(re-le+1);
		else
		{
			long long ans=0;
			push(u);
			if(rc<=mid)	ans=sum(ls,lc,rc);
			else
			{
				if(lc>=mid+1)	ans=sum(rs,lc,rc);
				else	ans=sum(ls,lc,mid)+sum(rs,mid+1,rc);
			}
			pull(u);
			return ans;
		}
	}
}xds;
struct LCT
{
	LCT()
	{
		memset(pre,-1,sizeof pre);
	}
	struct Edge
	{
		int v,nxt;
	}e[maxn];
	int pre[maxn],en;
	int lev[maxn],cnt[maxn];
	int fat[maxn],blo[maxn],pos[maxn],pn;
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].nxt=pre[v];pre[v]=en++; 
	}
	void build1(int u,int f,int l)
	{
		lev[u]=l;cnt[u]=1;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f)	build1(v,u,l+1),cnt[u]+=cnt[v];
		}
	}
	void build2(int u,int f,int bf,int l)
	{
		fat[u]=f;	blo[u]=bf;	lev[u]=l;	pos[u]=++pn;	idx[pn]=u;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f&&cnt[v]>cnt[u]/2)	build2(v,u,bf,l);
		}
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f&&cnt[v]<=cnt[u]/2)	build2(v,u,v,l+1);
		}
	}
	void add(int u,int v,int val)
	{
		while(blo[u]!=blo[v])
		{
			if(lev[u]>lev[v])	xds.add(1,pos[u],pos[blo[u]],val),u=fat[blo[u]];
			else	xds.add(1,pos[v],pos[blo[v]],val),v=fat[blo[v]];
		}
		xds.add(1,pos[u],pos[v],val);
	}
	long long sum(int u)
	{
		return xds.sum(1,pos[u],pos[u]+cnt[u]-1);
	}
}lct;
int main()
{
	int n;	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);	u++;	v++;
		lct.addedge(u,v);
	}
	lct.build1(1,0,1); 
	lct.build2(1,0,1,1);
	xds.build(1,n);
	int m;	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		char cmd[0];	int u,v,val;	scanf("%s",cmd);
		if(cmd[0]=='A')	scanf("%d%d%d",&u,&v,&val),u++,v++,lct.add(u,v,val);
		else	scanf("%d",&u),u++,printf("%lld\n",lct.sum(u));
	}
}
