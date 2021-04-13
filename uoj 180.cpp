#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100100;
int st1[maxn];
int st2[maxn];
int pos[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int le,re;
				int ls,rs;
				int mni;
		}n[maxn*3];
		int nn;
		void pull(int u)
		{
			if(n[u].ls!=0)	n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mni=st1[le];
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			}
			return u;
		}
		void optchg(int u,int p)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)
			{
				n[u].mni=1e9;
				return;
			}
			else
			{
				if(p<=mid)	optchg(n[u].ls,p);
				else	optchg(n[u].rs,p);
				pull(u);
			}
		}
		int qrymin(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==lc&&re==rc)	return n[u].mni;
			else
			{
				if(rc<=mid)	return qrymin(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymin(n[u].rs,lc,rc);
					else	return min(qrymin(n[u].ls,lc,mid),qrymin(n[u].rs,mid+1,rc));
				}
			}
		}
}xds;
int main()
{
	int n;	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&st1[i]);
		pos[st1[i]]=i;
	}
	xds.r=xds.build(1,n);
	for(int i=1;i<=n;i++)	scanf("%d",&st2[i]);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(pos[st2[i]]==1||xds.qrymin(xds.r,1,pos[st2[i]]-1)>st2[i])	xds.optchg(xds.r,pos[st2[i]]);
		else
		{
			ans=1;
			break;
		}
	}
	if(ans==0)	printf("YES\n");
	else	printf("NO\n");
} 
