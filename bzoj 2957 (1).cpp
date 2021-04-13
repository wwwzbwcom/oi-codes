#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=100100;
struct DivideBlock
{
	struct Node
	{
		int le,re;
		int x,y;
		int val;
	}n[maxn];
	int sto[maxn],idx[maxn],nn;
	void build(int tl)
	{
		int bl=sqrt(tl),cl=0;
		n[0].x=1;n[0].y=1;
		nn++;
		n[1].le=2;
		for(int i=1;i<=tl;i++)	sto[i]=1;
		for(int i=2;i<tl;i++)
		{
			cl++;
			idx[i]=nn;
			if(cl==bl)
			{
				n[nn].re=i;
				n[nn].x=n[nn].y=1;
				nn++;
				n[nn].le=i+1;
				cl=0;
			}
		}
		n[nn].re=tl;
		n[nn].x=n[nn].y=1;
	}
	void change(int x,int y)
	{
		sto[x]=y;
		int p=idx[x];
		if(y*n[p].x>n[p].y*x)	n[p].x=x,n[p].y=y;
		int xc=n[p-1].x,yc=n[p-1].y;
		n[p].val=0;
		for(int i=n[p].le;i<=n[p].re;i++)
		{
			if(sto[i]*xc>i*yc)	xc=i,yc=sto[i];
			else	if(sto[i]>0)	n[p].val++;
		}
		cout<<" "<<n[p].y<<" "<<n[p].x<<endl;
		for(int i=p+1;i<=nn;i++)
		{
			if(n[p].y*n[i].x>n[i].y*n[p].x)	n[i].x=n[p].x,n[i].y=n[p].y,n[i].val=0;
		}
	}
	int query()
	{
		int ans=0;
		for(int i=1;i<=nn;i++)	ans+=n[i].val;
		return ans;
	}
}db;
int main()
{
	int n,m;	scanf("%d%d",&n,&m);
	db.build(n+1);
	for(int i=1;i<=m;i++)
	{
		int x,y;	scanf("%d%d",&x,&y);
		x++;	y++;
		db.change(x,y);
		printf("%d\n",db.query());
	}
}
