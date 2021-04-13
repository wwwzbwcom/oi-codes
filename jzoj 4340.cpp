#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=500100;
const int oo=-1e8;
int sto[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int le,re;
				int ls,rs;
				int sum;
				int mxa,mni;
				int cmx,cmn;
				int smx,smn;
				int mad,mmx,mmn;
		}n[maxn*2];
		int nn;
		void push(int u)
		{
			if(n[u].ls!=0)
			{
				int ls=n[u].ls,rs=n[u].rs;
				n[ls].mad+=n[u].mad;	n[rs].mad+=n[u].mad;	n[u].mad=0;
				n[] 
			}
		}
		void pull(int u)
		{
			if(n[u].ls!=0)
			{
				int ls=n[u].ls,rs=n[u].rs;
				n[u].sum=n[ls].sum+n[rs].sum;
				n[u].mxa=max(n[ls].mxa,n[rs].mxa);
				n[u].mni=min(n[ls].mni,n[rs].mni);
				n[u].cmx=n[ls].cmx*(n[u].mxa==n[ls].mxa)+n[rs].cmx*(n[u].mxa==n[rs].mxa);
				n[u].cmn=n[ls].cmn*(n[u].mni==n[ls].mni)+n[rs].cmn*(n[u].mni==n[rs].mni);
				n[u].smx=max(n[ls].smx,n[rs].smx);
				n[u].smn=min(n[ls].smn,n[rs].smn);
			}
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].sum=n[u].mxa=n[u].mni=sto[le],n[u].cmx=n[u].cmn=n[u].cnt=1,n[u].smx=n[u].smn=-oo;
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u); 
			}
			return u;
		}
		void operate(int u,int lc,int rc,int val,int mod)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==lc&&re==rc)
			{
				if(mod==0)	n[u].sum+=n[u].cnt*val,n[u].mxa+=val,n[u].mni+=val,n[u].smx+=val,n[u].smn+=val;
				if(mod==1)
				{
					if(val>n[u].mni)
						if(val<=n[u].smn)	n[u].sum+=n[u].cmn*(val-n[u].mni);
						else
						{
							push(u);
							operate(n[u].ls,lc,mid,val,1),operate(n[u].rs,mid+1,rc,val,1);
							pull(u);
						}
					n[u].mni=max(n[u].mni,val);
				}
				if(mod==2)
				{
					if(val<n[u].mxa)
						if(val>=n[u].smx)	n[u].sum-=n[u].cmx*(val-n[u].mxa);
						else
						{
							push(u);
							operate(n[u].ls,lc,mid,val,2),operate(n[u].rs,mid+1,rc,val,2);
							pull(u);
						}
					n[u].mxa=min(n[u].mxa,val); 
				}
			}
			else
			{
				push(u);
				cout<<le<<"="<<re<<"="<<lc<<" "<<rc<<" "<<mod<<endl;
				if(rc<=mid)	operate(n[u].ls,lc,rc,val,mod);
				else
				{
					if(lc>=mid+1)	operate(n[u].rs,lc,rc,val,mod);
					else	operate(n[u].ls,lc,mid,val,mod),operate(n[u].rs,mid+1,rc,val,mod);
				}
				pull(u);	
			}
		}
		int query(int u,int lc,int rc,int mod)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==lc&&re==rc)
			{
				if(mod==0)	return n[u].sum;
				if(mod==1)	return n[u].mxa;
				if(mod==2)	return n[u].mni;
			}
			else
			{
				if(rc<=mid)	query(n[u].ls,lc,rc,mod);
				else
				{
					if(lc>=mid+1)	query(n[u].rs,lc,rc,mod);
					else
					{
						int a=query(n[u].ls,lc,mid,mod),b=query(n[u].rs,mid+1,rc,mod);
						if(mod==0)	return a+b;
						if(mod==1)	return max(a,b);
						if(mod==2)	return min(a,b); 
					}
				}
			}
		}	
}xds;
int main()
{
	freopen("wyywyy1.in","r",stdin);
	freopen("wyywyy.out","w",stdout);
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>sto[i];
	xds.r=xds.build(1,n);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cout<<i<<'='<<endl;
		int cmd,l,r,x;	cin>>cmd>>l>>r;
		if(cmd==1)	cin>>x,xds.operate(xds.r,l,r,x,0);
		if(cmd==2)	cin>>x,xds.operate(xds.r,l,r,x,1);
		if(cmd==3)	cin>>x,xds.operate(xds.r,l,r,x,2);
		if(cmd==4)	cout<<xds.query(xds.r,l,r,0)<<endl;
		if(cmd==5)	cout<<xds.query(xds.r,l,r,1)<<endl;
		if(cmd==6)	cout<<xds.query(xds.r,l,r,2)<<endl;
	}
}
