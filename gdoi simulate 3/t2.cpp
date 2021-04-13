#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=200100;
int n,m;
int sto[maxn];
struct XDS
{
	struct Node
	{
		Node()
		{
			ls=rs=NULL;
			le=re=0;
			lsum=rsum=tsum=msum=0;
		}
		Node *ls,*rs;
		int le,re;
		int lsum,rsum,tsum,msum;
	};
	Node *r;
	void pull(Node *u)
	{
		Node *ls=u->ls,*rs=u->rs;
		if(ls!=NULL)
		{
			u->lsum=max(ls->lsum,ls->tsum+rs->lsum);
			u->rsum=max(rs->rsum,rs->tsum+ls->rsum);
			u->tsum=ls->tsum+rs->tsum;
			u->msum=max(max(ls->msum,rs->msum),ls->rsum+rs->lsum);
		}
	}
	Node *build(int le,int re)
	{
		Node *u=new Node;
		u->le=le,u->re=re;
		if(le==re)	u->lsum=u->rsum=u->tsum=u->msum=sto[le];
		else
		{
			int mid=(le+re)/2;
			u->ls=build(le,mid);
			u->rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	void set(Node *u,int p,int v)
	{
		Node *ls=u->ls,*rs=u->rs;
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
		if(le==re)	u->lsum=u->rsum=u->tsum=u->msum=v;
		else
		{
			if(p<=mid)	set(ls,p,v);
			else	set(rs,p,v);
			pull(u);
		}
	}
}xds;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);	u++;	v++;
	}
	xds.r=xds.build(1,n);
	for(int i=1;i<=m;i++)
	{
		int p,v;	scanf("%d%d",&p,&v);	p++;
		xds.set(xds.r,p,v);
		printf("%d\n",xds.r->msum);
	}
}
