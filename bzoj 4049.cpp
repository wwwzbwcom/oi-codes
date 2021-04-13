#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100100;
int n,m;
int sto[maxn];
long long ans=0; 
struct XDS
{
	struct Node
	{
		int ls,rs;
		int le,re;
		int sum[2][2];
	}n[maxn*2];
	int nn;
	void pull(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		if(ls!=0)
		{
			n[u].sum[0][0]=max(max(max(n[ls].sum[0][0],n[ls].sum[0][1]),max(n[rs].sum[0][0],n[rs].sum[1][0])),n[ls].sum[0][1]+n[rs].sum[1][0]);
			n[u].sum[0][1]=max(n[rs].sum[0][1],n[ls].sum[0][1]+n[rs].sum[1][1]);
			n[u].sum[1][0]=max(n[ls].sum[1][0],n[ls].sum[1][1]+n[rs].sum[1][0]);
			n[u].sum[1][1]=n[ls].sum[1][1]+n[rs].sum[1][1];
		}
	}
	int build(int le,int re)
	{
		int u=++nn;
		n[u].le=le;	n[u].re=re;
		if(le==re)	n[u].sum[1][1]=sto[le];
		else
		{
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	void change(int u,int pos,int val)
	{
		int ls=n[u].ls,rs=n[u].rs;
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		
		if(le==re)	n[u].sum[1][1]=val;
		else
		{
			if(pos<=mid)	change(ls,pos,val);
			else	change(rs,pos,val);
			pull(u);
		}
	}
	int getans()
	{
		return max(max(n[1].sum[0][0],n[1].sum[0][1]),max(n[1].sum[1][0],n[1].sum[1][1]));
	}
}xds;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	xds.build(1,n);
	for(int i=1;i<=m;i++)
	{
		int pos,val;	scanf("%d%d",&pos,&val);
		xds.change(1,pos,val);
		ans+=xds.getans();
	}
	printf("%lld",ans);
}
