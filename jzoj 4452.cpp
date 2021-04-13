#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100010;
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int mxa;
		}n[maxn*3];
		int nn;
	public:
		int r;
		void init()
		{
			nn=r=0;
		}
		int build(int le,int re)
		{
			int u=++nn;
			if(le==re)	n[u].ls=n[u].rs=0,n[u].mxa=0;
			else
			{
				int mid=(le+re)>>1;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re); 
				n[u].mxa=max(n[n[u].ls].mxa,n[n[u].rs].mxa);
			}
			return u;
		}
		void optchg(int u,int le,int re,int pos,int val)
		{
			if(le==re)	n[u].mxa=val;
			else
			{
				int mid=(le+re)>>1;
				if(pos<=mid)	optchg(n[u].ls,le,mid,pos,val);
				else	optchg(n[u].rs,mid+1,re,pos,val);
				n[u].mxa=max(n[n[u].ls].mxa,n[n[u].rs].mxa);
			}
		}
		int qrymxa(int u,int le,int re,int lc,int rc)
		{
			if(le==lc&&re==rc)	return n[u].mxa;
			else
			{
				int mid=(le+re)>>1;
				if(rc<=mid)	return qrymxa(n[u].ls,le,mid,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymxa(n[u].rs,mid+1,re,lc,rc);
					else	return max(qrymxa(n[u].ls,le,mid,lc,mid),qrymxa(n[u].rs,mid+1,re,mid+1,rc));
				}
			}
		}
}xd;
int n,q;
int sto[maxn];
int tmp[maxn],tn;
int bac[maxn];
int lef[maxn],rig[maxn];
void init()
{
	xd.init();
	xd.r=xd.build(1,n);
	for(int i=1;i<=n;i++)
	{
		if(sto[i]-1>=1)	lef[i]=(xd.qrymxa(xd.r,1,n,1,sto[i]-1)+1);
		else	lef[i]=1;
		xd.optchg(xd.r,1,n,sto[i],i);
	}
	xd.init();
	xd.r=xd.build(1,n);
	reverse(sto+1,sto+n+1);
	for(int i=1;i<=n;i++) 
	{
		rig[(n+1)-i]=(n+1)-(xd.qrymxa(xd.r,1,n,1,sto[i])+1);
		xd.optchg(xd.r,1,n,sto[i],i);
	}
	reverse(sto+1,sto+n+1);
}
int main()
{
	scanf("%d%d",&n,&q);	tn=n;
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]),tmp[i]=sto[i],bac[i]=sto[i];
	sort(tmp+1,tmp+tn+1);
	tn=unique(tmp+1,tmp+tn+1)-(tmp+1);
	for(int i=1;i<=n;i++)	sto[i]=lower_bound(tmp+1,tmp+n+1,sto[i])-tmp;
//	for(int i=1;i<=n;i++)	cout<<sto[i]<<" ";
//	cout<<endl;
	init();
	for(int i=1;i<=q;i++)
	{
		int l,r;	scanf("%d%d",&l,&r);
		long long ans=0;
	//	cout<<i<<"============="<<endl;
		for(int j=l;j<=r;j++)
		{
		//	cout<<j<<" "<<((j-max(lef[j],l)+1)*(min(rig[j],r)-j+1))<<" "<<sto[j]<<endl;
			ans+=((long long)(j-max(lef[j],l)+1)*(min(rig[j],r)-j+1))*bac[j];
		}
		printf("%lld\n",ans);
	}
}
