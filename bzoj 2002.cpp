//#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
struct Block
{
	int l,r;
}b[200100];
int dis[200100];
int bel[200100];
int ste[200100];
int pla[200100];
int n,m;
int bn,len;
void init()
{
	len=(int)sqrt(n);
	bn++;
	b[bn].l=1;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		bel[i]=bn;
		cnt++;
		if(i!=n&&cnt==len)
		{
			b[bn].r=i;
			bn++;
			b[bn].l=i+1;
			cnt=0;
		}
	}
	b[bn].r=n;
	bn++;
	for(int i=n;i>=1;i--)
	{
		int u=i,v=i+dis[u];
		if(bel[u]==bel[v])	ste[u]=ste[v]+1,pla[u]=pla[v];
		else	ste[u]=1,pla[u]=v;
	}
}
int query(int u)
{
	int ans=0,v=u;
	while(v<=n)
	{
		ans+=ste[v];
		v=pla[v];
	}
	return ans;
}
void change(int u,int val)
{
	dis[u]=val;
	for(int i=u;i>=b[bel[u]].l;i--)
	{
		int u=i,v=i+dis[v];
		if(bel[u]==bel[v])	ste[u]=ste[v]+1,pla[u]=pla[v];
		else	ste[u]=1,pla[u]=v;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&dis[i]);
	init();
//	for(int i=1;i<=n;i++)	cout<<i<<"="<<ste[i]<<"="<<pla[i]<<endl;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int cmd,pos,val;	scanf("%d%d",&cmd,&pos);	pos++;
		if(cmd==1)	printf("%d\n",query(pos));
		else	scanf("%d",&val),change(pos,val);
	}
}
