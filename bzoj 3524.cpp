#include<algorithm>
#include<cstdio>
using namespace std;
struct ZhuXiShu
{
	struct Node
	{
		int ls,rs;
		int sum;
	}n[500000*20+100];
	int nn;
	int r[500100];
	void pull(int u)
	{
		n[u].sum=n[n[u].ls].sum+n[n[u].rs].sum;
	}
	void copy(int a,int b)
	{
		n[a].ls=n[b].ls;
		n[a].rs=n[b].rs;
		n[a].sum=n[b].sum;
	}
	void add(int u,int le,int re,int pos)
	{
		int mid=(le+re)/2;	
		
		if(le==re)	n[u].sum++;
		else
		{
			if(pos<=mid)
			{
				int ols=n[u].ls;
				n[u].ls=++nn;
				copy(n[u].ls,ols);
				add(n[u].ls,le,mid,pos);
			}
			else
			{
				int ors=n[u].rs;
				n[u].rs=++nn;
				copy(n[u].rs,ors);
				add(n[u].rs,mid+1,re,pos);
			}
			pull(u);
		}
		
	}
	int query(int su,int eu,int le,int re,int len)
	{
	//	cout<<le<<" "<<re<<endl;
		if(le==re)
		{
			if(n[eu].sum-n[su].sum>len/2)	return le;
			else	return 0;
		}
		int mid=(le+re)/2;
		if(n[n[eu].ls].sum-n[n[su].ls].sum>n[n[eu].rs].sum-n[n[su].rs].sum)	return query(n[su].ls,n[eu].ls,le,mid,len);
		else
		{
			if(n[n[eu].ls].sum-n[n[su].ls].sum==n[n[eu].rs].sum-n[n[su].rs].sum)	return 0;
			else	return query(n[su].rs,n[eu].rs,mid+1,re,len);
		}
	}
	void debug()
	{
		printf("=========================\n");
		for(int i=1;i<=nn;i++)
		{
			printf("%d %d=%d %d\n",i,n[i].ls,n[i].rs,n[i].sum);
		}
	}
}z;
int n,m;
int pos[500100];
int sto[500100],sn;
int idx[500100];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&pos[i]),sto[sn++]=pos[i];
	sort(sto,sto+sn);
	sn=unique(sto,sto+sn)-sto;
	for(int i=1;i<=n;i++)	pos[i]=lower_bound(sto,sto+sn,pos[i])-sto+1;
	for(int i=0;i<sn;i++)	idx[i+1]=sto[i];
	
	for(int i=1;i<=n;i++)
	{
		z.r[i]=++z.nn;
		z.copy(z.r[i],z.r[i-1]);
		z.add(z.r[i],1,sn,pos[i]);
	}
	
	for(int i=1;i<=m;i++)
	{
		int s,e;	scanf("%d%d",&s,&e);
		printf("%d\n",idx[z.query(z.r[s-1],z.r[e],1,sn,e-s+1)]);
	}
}
