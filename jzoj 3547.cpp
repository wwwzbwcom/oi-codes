#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=2e5+10;
class XDS
{
	public:
		class Node
		{
			public:
				Node()
				{
					mni=0;
					ls=rs=0;
				}
				int mni;
				int ls,rs;
		}n[maxn*40];
		int r[maxn];
		int nn;
		void pull(int u)
		{
			if(n[u].ls!=0)	n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
		}
		int build(int le,int re)
		{
			int mid=(le+re)/2;
			int u=++nn;
			if(le==re)	n[u].mni=0;
			else
			{
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			}
			return u;
		}
		void optchg(int u,int le,int re,int pos,int val)
		{
			int mid=(le+re)/2;
			if(le==re)	n[u].mni=val;
			else
			{
				if(pos<=mid)
				{
					Node p=n[n[u].ls];	n[u].ls=++nn;	n[n[u].ls]=p;
					optchg(n[u].ls,le,mid,pos,val);
				}
				else
				{
					Node p=n[n[u].rs];	n[u].rs=++nn;	n[n[u].rs]=p;
					optchg(n[u].rs,mid+1,re,pos,val);
				}
				pull(u);
			}
		}
		int qrymin(int u,int le,int re,int lc,int rc)
		{
			int mid=(le+re)/2;
			if(le==lc&&re==rc)	return n[u].mni;
			else
			{
				if(rc<=mid)	return qrymin(n[u].ls,le,mid,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymin(n[u].rs,mid+1,re,lc,rc);
					else	return min(qrymin(n[u].ls,le,mid,lc,mid),qrymin(n[u].rs,mid+1,re,mid+1,rc));
				}
			}
		}
}xd;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	xd.r[0]=xd.build(0,n);
	for(int i=1;i<=n;i++)
	{
		int val;	scanf("%d",&val);
		xd.r[i]=++xd.nn;	xd.n[xd.r[i]]=xd.n[xd.r[i-1]];
		if(val<=n)	xd.optchg(xd.r[i],0,n,val,i);
	}
	for(int i=1;i<=m;i++)
	{
		int lc,rc;	scanf("%d%d",&lc,&rc);
		int l=0,r=n,ans=n;
		while(l<=r)
		{
			int m=(l+r)/2;
			if(xd.qrymin(xd.r[rc],0,n,0,m)>=lc)	l=m+1;
			else	ans=m,r=m-1;
		}
		printf("%d\n",ans);
	}
}
