#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=100100;
int n;
int hei[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int mxa;
		}n[maxn*3];
		int nn;
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mxa=hei[le]+ceil(sqrt(le-1));
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				n[u].mxa=max(n[n[u].ls].mxa,n[n[u].rs].mxa);
			}
			return u;
		}
		void optchg(int u,int pos,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)	n[u].mxa=val;
			else
			{
				if(pos<=mid)	optchg(n[u].ls,pos,val);
				else	optchg(n[u].rs,pos,val);
				n[u].mxa=max(n[n[u].ls].mxa,n[n[u].rs].mxa);
			}
		}
		int qrymxa(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==lc&&re==rc)	return n[u].mxa;
			else
			{
				if(rc<=mid)	return qrymxa(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymxa(n[u].rs,lc,rc);
					else	return max(qrymxa(n[u].ls,lc,mid),qrymxa(n[u].rs,mid+1,rc));
				}
			}
		}
}xd;
int main()
{
	freopen("light.in","r",stdin);
//	freopen("light.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&hei[i]);
	xd.r=xd.build(1,n);
	//printf("%d\n",max(0,xd.qrymxa(xd.r,1,n)-hei[1]));
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j*j<=n;j++)
		{
			int k;
			k=i-j*j-1;	if(k>=1)	xd.optchg(xd.r,k,hei[k]+ceil(sqrt(abs(i-k))));//cout<<k<<" "<<hei[k]+ceil(sqrt(abs(i-k)))<<endl;
			k=i+j*j;	if(k<=n)	xd.optchg(xd.r,k,hei[k]+ceil(sqrt(abs(i-k))));//cout<<k<<" "<<hei[k]+ceil(sqrt(abs(i-k)))<<endl;
		}
		if(max(0,xd.qrymxa(xd.r,1,n)-hei[i])==7493)
		printf("%d %d\n",i,max(0,xd.qrymxa(xd.r,1,n)-hei[i]));
	}
}
