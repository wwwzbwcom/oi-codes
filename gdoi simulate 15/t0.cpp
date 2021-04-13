#include<iostream>
#include<cstring>
using namespace std;
const int maxn=100100;
class XDS
{
	private:
		class Node
		{
			public:
				Node()
				{
					le=re=ls=rs=sum=0;
					memset(m,0,sizeof m);
					memset(l,0,sizeof l);
					memset(r,0,sizeof r);
					memset(s,0,sizeof s);
				}
				int le,re;
				int ls,rs;
				int m[21],l[21],r[21],s[21],sum;
		}n[maxn*2];
		class Ret
		{
			public:
				Ret()
				{
					sum=0;
					memset(m,0,sizeof m);
					memset(l,0,sizeof l);
					memset(r,0,sizeof r);
					memset(s,0,sizeof s);
				}
				int m[21],l[21],r[21],s[21],sum;
		};
		void pull(int u)
		{
			int ls=n[u].ls,rs=n[u].rs;
			memset(n[u].m,0,sizeof n[u].m);
			memset(n[u].l,0,sizeof n[u].l);
			memset(n[u].r,0,sizeof n[u].r);
			memset(n[u].s,0,sizeof n[u].s);
			n[u].sum=0;
			for(int i=0;i<=20;i++)
				for(int j=0;j<=20;j++)
				{
					if(i+j<=20)		n[u].m[i+j]    =max(n[u].m[i+j],n[ls].m[i]+n[rs].m[j]);
					if(i+j+1<=20)	n[u].m[i+j+1]  =max(n[u].m[i+j+1],n[ls].r[i]+n[rs].l[j]);
					
					if(i+j<=20)		n[u].l[i+j]    =max(n[u].l[i+j],n[ls].l[i]+n[rs].m[j]);
					if(i+j+1<=20)	n[u].l[i+j+1]  =max(n[u].l[i+j+1],n[ls].s[i]+n[rs].l[j]);
					
					if(i+j<=20)		n[u].r[i+j]    =max(n[u].r[i+j],n[ls].m[i]+n[rs].r[j]);
					if(i+j+1<=20)	n[u].r[i+j+1]  =max(n[u].r[i+j+1],n[ls].r[i]+n[rs].s[j]);
					
					if(i+j<=20)		n[u].s[i+j]    =max(n[u].s[i+j],n[ls].l[i]+n[rs].r[i]);
					if(i+j+1<=20)	n[u].s[i+j+1]  =max(n[u].s[i+j+1],n[ls].s[i]+n[rs].s[j]);
				}
			
			for(int i=0;i<=20;i++)
			{
				n[u].l[i]=max(n[u].l[i],n[ls].sum+n[rs].l[i]);
				n[u].r[i]=max(n[u].r[i],n[rs].sum+n[ls].r[i]);
				n[u].s[i]=max(n[u].s[i],n[ls].sum+n[rs].s[i]);
				n[u].s[i]=max(n[u].s[i],n[rs].sum+n[ls].s[i]);
			}
			n[u].l[0]=max(n[u].l[0],n[ls].sum+n[rs].sum);
			n[u].r[0]=max(n[u].r[0],n[ls].sum+n[rs].sum);
			n[u].s[0]=max(n[u].s[0],n[ls].sum+n[rs].sum);
			n[u].sum=n[ls].sum+n[rs].sum;
		}
		Ret convert(const Node &in)
		{
			Ret ans;
			memcpy(ans.m,in.m,sizeof in.m);
			memcpy(ans.l,in.l,sizeof in.l);
			memcpy(ans.r,in.r,sizeof in.r);
			memcpy(ans.s,in.s,sizeof in.s);
			ans.sum=in.sum;
			return ans;
		}
		Ret merge(const Ret &ls,const Ret &rs)
		{
			Ret ans;
			ans.sum=0;
			for(int i=0;i<=20;i++)
				for(int j=0;j<=20;j++)
				{
					if(i+j<=20)		ans.m[i+j]    =max(ans.m[i+j],ls.m[i]+rs.m[j]);
					if(i+j+1<=20)	ans.m[i+j+1]  =max(ans.m[i+j+1],ls.r[i]+rs.l[j]);
					
					if(i+j<=20)		ans.l[i+j]    =max(ans.l[i+j],ls.l[i]+rs.m[j]);
					if(i+j+1<=20)	ans.l[i+j+1]  =max(ans.l[i+j+1],ls.s[i]+rs.l[j]);
					
					if(i+j<=20)		ans.r[i+j]    =max(ans.r[i+j],ls.m[i]+rs.r[j]);
					if(i+j+1<=20)	ans.r[i+j+1]  =max(ans.r[i+j+1],ls.r[i]+rs.s[j]);
					
					if(i+j<=20)		ans.s[i+j]    =max(ans.s[i+j],ls.l[i]+rs.r[i]);
					if(i+j+1<=20)	ans.s[i+j+1]  =max(ans.s[i+j+1],ls.s[i]+rs.s[j]);
				}
			
			for(int i=0;i<=20;i++)
			{
				ans.l[i]=max(ans.l[i],ls.sum+rs.l[i]);
				ans.r[i]=max(ans.r[i],rs.sum+ls.r[i]);
				ans.s[i]=max(ans.s[i],ls.sum+rs.s[i]);
				ans.s[i]=max(ans.s[i],rs.sum+ls.s[i]);
			}
			ans.l[0]=max(ans.l[0],ls.sum+rs.sum);
			ans.r[0]=max(ans.r[0],ls.sum+rs.sum);
			ans.s[0]=max(ans.s[0],ls.sum+rs.sum);
			ans.sum=ls.sum+rs.sum;
			return ans;
		}
		int nn;
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)
			{
				int val;	cin>>val;
				memset(n[u].m,0,sizeof n[u].m);
				memset(n[u].l,0,sizeof n[u].l);
				memset(n[u].r,0,sizeof n[u].r);
				memset(n[u].s,0,sizeof n[u].s);
				n[u].m[1]=n[u].l[0]=n[u].r[0]=n[u].s[0]=n[u].sum=val;
			}
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			//	cout<<le<<" "<<re<<" "<<n[u].m[10]<<" "<<n[u].l[0]<<" "<<n[u].r[0]<<" "<<n[u].s[0]<<endl;
			}
			return u;
		}
		void change(int u,int pos,int val)
		{
			int le=n[u].le,re=n[u].re;
			if(le==re&&le==pos)
			{
				memset(n[u].m,0,sizeof n[u].m);
				memset(n[u].l,0,sizeof n[u].l);
				memset(n[u].r,0,sizeof n[u].r);
				memset(n[u].s,0,sizeof n[u].s);
				n[u].m[1]=n[u].l[0]=n[u].r[0]=n[u].s[0]=n[u].sum=val;
			} 
			else
			{
				int mid=(le+re)/2;
				if(pos<=mid)	change(n[u].ls,pos,val);
				else	change(n[u].rs,pos,val);
				pull(u);
			//	cout<<le<<" "<<re<<" "<<n[u].m[0]<<endl;
			}
		}
		Ret query(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
		//	cout<<le<<" "<<re<<endl;
			if(le==lc&&re==rc)
			{
			//	cout<<le<<"="<<re<<endl;
				return convert(n[u]);
				
			}
			else
			{
				if(rc<=mid)	return query(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return query(n[u].rs,lc,rc);
					else
					{
					//	cout<<lc<<"="<<mid<<"="<<mid+1<<"="<<rc<<endl;
						return merge(query(n[u].ls,lc,mid),query(n[u].rs,mid+1,rc));
					}
				}
			}
		}
		int queryinit(int lc,int rc,int k)
		{
			Ret in=query(r,lc,rc);
			int ans=0;
			for(int i=0;i<=k;i++)//	cout<<i<<"="<<in.m[i]<<endl,
			ans=max(ans,in.m[i]);
			return ans;
		}
}xds;
int n,m;
int main()
{
//	freopen("data0.txt","r",stdin);
	cin>>n;
	xds.r=xds.build(1,n);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		//cout<<i<<endl;
		int cmd;	cin>>cmd;
		if(cmd==0)
		{
			int i,val;	cin>>i>>val;
			xds.change(xds.r,i,val); 
		}
		if(cmd==1)
		{
			int l,r,k;	cin>>l>>r>>k;
			cout<<xds.queryinit(l,r,k)<<endl;
		}
	}
}
