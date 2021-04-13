#include<cstdio>
using namespace std;
struct XDS
{
	struct Node
	{
		int ls,rs;
		int le,re;
		int con,sum,len;
	}n[200100];
	int nn;
	int build(int le,int re)
	{
		int u=++nn;
		n[u].le=le;	n[u].re=re;	n[u].len=re-le+1;
		if(le==re)	n[u].ls=n[u].rs=0;
		else
		{
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	void push(int u)
	{
		if(n[u].con==1&&n[u].ls!=0)
		{
			n[n[u].ls].con^=1;
			n[n[u].rs].con^=1;
			n[u].con=0;
		}
		pull(u);
	}
	void pull(int u)
	{
		n[u].sum=0;
		if(n[n[u].ls].con==1)	n[u].sum+=n[n[u].ls].len-n[n[u].ls].sum;	else	n[u].sum+=n[n[u].ls].sum;
		if(n[n[u].rs].con==1)	n[u].sum+=n[n[u].rs].len-n[n[u].rs].sum;	else	n[u].sum+=n[n[u].rs].sum;
	}
	void change(int u,int lc,int rc)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		
		push(u);
		if(le==lc&&re==rc)
		{
			n[u].con^=1;
			return; 
		}
		if(rc<=mid)	change(n[u].ls,lc,rc);
		else
		{
			if(lc>=mid+1)	change(n[u].rs,lc,rc);
			else	change(n[u].ls,lc,mid),change(n[u].rs,mid+1,rc);
		}
		pull(u);
	}
	int query(int u,int lc,int rc)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		
		push(u);
		if(le==lc&&re==rc)
		{
			if(n[u].con==1)	return n[u].len-n[u].sum;
			else	return	n[u].sum; 
		}
		int ans;
		if(rc<=mid)	ans=query(n[u].ls,lc,rc);
		else
		{
			if(lc>=mid+1)	ans=query(n[u].rs,lc,rc);
			else	ans=query(n[u].ls,lc,mid)+query(n[u].rs,mid+1,rc);
		}
		pull(u);
		return ans;
	}
}xd;
int main()
{
	int n,m;	scanf("%d%d",&n,&m);
	xd.build(1,n);
	for(int i=1;i<=m;i++)
	{
		int cmd,l,r;	scanf("%d%d%d",&cmd,&l,&r);
		if(cmd==0)	xd.change(1,l,r);
		if(cmd==1)	printf("%d\n",xd.query(1,l,r));
	}
}
