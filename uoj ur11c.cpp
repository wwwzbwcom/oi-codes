#include<iostream>
using namespace std;
const int maxn=5e5+100;
int n,m;
int sto[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int le,re;
				int ls,rs;
				int add,mni,hmn;
		}n[maxn*3];
		int nn;
		void pull(int u)
		{
			int ls=n[u].ls,rs=n[u].rs;
			if(ls!=0)
			{
			//	cout<<n[ls].mni<<"~"<<n[rs].mni<<endl;
				n[u].mni=min(n[ls].mni+n[ls].add,n[rs].mni+n[rs].add);
				n[u].hmn=min(n[u].hmn,n[u].mni);
			}
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mni=n[u].hmn=sto[le];
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
				n[u].hmn=n[u].mni;
			}
			return u;
		}
		void optadd(int u,int lc,int rc,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			
			
		//	getchar();
			if(le==lc&&re==rc)
			{	
				n[u].add+=val;
			//	cout<<le<<"="<<re<<" "<<lc<<"="<<rc<<" "<<n[u].add<<endl;
			}
			else
			{
				if(rc<=mid)	optadd(n[u].ls,lc,rc,val);
				else
				{
					if(lc>=mid+1)	optadd(n[u].rs,lc,rc,val);
					else	optadd(n[u].ls,lc,mid,val),optadd(n[u].rs,mid+1,rc,val);
				}
				//cout<<"============="<<endl;
				pull(u);
			}
		}
		int qrymni(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
		
			if(le==lc&&re==rc)	return	n[u].mni+n[u].add;
			else
			{
				int ans;
				if(rc<=mid)	ans=qrymni(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	ans=qrymni(n[u].rs,lc,rc);
					else	ans=min(qrymni(n[u].ls,lc,mid),qrymni(n[u].rs,mid+1,rc)); 
				}
				return ans+n[u].add;
			}
		}
		int qryhmn(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			
			if(le==lc&&re==rc)	return	min(n[u].hmn,n[u].mni+n[u].add);
			else
			{
				int ans;
				if(rc<=mid)	ans=qryhmn(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	ans=qryhmn(n[u].rs,lc,rc);
					else	ans=min(qryhmn(n[u].ls,lc,mid),qryhmn(n[u].rs,mid+1,rc)); 
				}
				return ans+n[u].add;
			}
		}
}xd;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>sto[i];
	xd.r=xd.build(1,n);
	for(int i=1;i<=m;i++)
	{
		int cmd,l,r,c;
		cin>>cmd;
		if(cmd==1)	cin>>l>>r>>c,xd.optadd(xd.r,l,r,c);
		if(cmd==2)
		{
			cin>>l>>r>>c;
			for(int i=l;i<=r;i++)
			{
				int t=xd.qrymni(xd.r,i,i);
				if(t<c)	xd.optadd(xd.r,i,i,c-t);
			}
		}
		if(cmd==3)	cin>>l>>r,cout<<xd.qrymni(xd.r,l,r)<<endl;
		if(cmd==4)	cin>>l>>r,cout<<xd.qryhmn(xd.r,l,r)<<endl;
	}
}
