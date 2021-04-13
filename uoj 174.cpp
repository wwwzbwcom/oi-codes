#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100100;
int num;
int a[maxn];
int que[maxn],lq=0,rq=0;
struct XDS
{
	struct NODE
	{
		int ls,rs;
		int le,re;
		int mv,mp;
		int fv,fp;
	}n[maxn*2];
	int nn,r;
	void init()
	{
		int nn=0;
	}
	void pull(int u)
	{
		if(n[u].ls!=0)
		{
			if(n[n[u].ls].mv<n[n[u].rs].mv)	n[u].mv=n[n[u].ls].mv,n[u].mp=n[n[u].ls].mp;
			else							n[u].mv=n[n[u].rs].mv,n[u].mp=n[n[u].rs].mp;
			
			if(n[n[u].ls].fp!=-1)	n[u].fv=n[n[u].ls].fv,n[u].fp=n[n[u].ls].fp;
			else					n[u].fv=n[n[u].rs].fv,n[u].fp=n[n[u].rs].fp;
		}
	}
	int build(int le,int re)
	{
		int u=++nn;
		int mid=(le+re)>>1;
		n[u].le=le;	n[u].re=re;
		if(le==re)
		{
			n[u].ls=n[u].rs=0;
			n[u].mv=n[u].fv=a[le];
			n[u].mp=n[u].fp=le;
		}
		else
		{
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	void operate(int u,int p)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
		if(le==re)	n[u].mv=1e9,n[u].mp=le,n[u].fv=n[u].fp=-1;
		else
		{
			if(p<=mid)	operate(n[u].ls,p);
			else		operate(n[u].rs,p);
			pull(u);
		}
	}
}xd;
int gn;
int main()
{
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%d",&num);
		for(int i=1;i<=num;i++)	scanf("%d",&a[i]);
		xd.init();
		xd.r=xd.build(1,num);
		while(xd.n[xd.r].mv!=1e9)
		{
			if(lq>=rq||xd.n[xd.r].mv<min(que[lq],que[rq-1]))
			{
				while(1)
				{
					int flag=0;
					que[rq++]=xd.n[xd.r].fv;
					if(xd.n[xd.r].fv==xd.n[xd.r].mv)	flag=1;
					xd.operate(xd.r,xd.n[xd.r].fp);
					if(flag)	break;
				}
				printf("%d ",que[--rq]);
			}
			else
			{
				if(que[lq]<que[rq-1])	printf("%d ",que[lq++]);
				else	printf("%d ",que[--rq]);
			}
		}
		while(lq<rq)
		{
			if(que[lq]<que[rq-1])	printf("%d ",que[lq++]);
			else	printf("%d ",que[--rq]);
		}
		printf("\n");
	}
	
}
