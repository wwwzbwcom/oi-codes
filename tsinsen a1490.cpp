#include<iostream>
using namespace std;
const int maxn=500500;
int n,m;
double val[maxn];
inline double getans(double in)
{
	return in*in+in+1;
}
struct XDS
{
	struct NODE
	{
		int ls,rs;
		int le,re;
		int len;
		double lef,rig,pos,ans;
	}n[maxn*3];
	int nn,r;
	struct CON
	{
		CON(const NODE &in)
		{
			len=in.len;
			lef=in.lef,rig=in.rig,pos=in.pos,ans=in.ans;
		}
		CON(){}
		int len;
		double lef,rig,pos,ans;
	};
	CON merge(const CON &ls,const CON &rs)
	{
		CON ret;
		ret.pos=ls.pos*rs.pos;
		ret.lef=ls.lef*(1-ls.pos)+(ls.len+rs.lef)*ls.pos;
		ret.rig=rs.rig*(1-rs.pos)+(rs.len+ls.rig)*rs.pos;
		ret.ans=ls.ans-getans(ls.rig)+rs.ans-getans(rs.lef)+getans(ls.rig+rs.lef);
		return ret;
	}
	void pull(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		n[u].pos=n[ls].pos*n[rs].pos;
		n[u].lef=n[ls].lef*(1-n[ls].pos)+(n[ls].len+n[rs].lef)*n[ls].pos;
		n[u].rig=n[rs].rig*(1-n[rs].pos)+(n[rs].len+n[ls].rig)*n[rs].pos;
		n[u].ans=n[ls].ans-getans(n[ls].rig)+n[rs].ans-getans(n[rs].lef)+getans(n[ls].rig+n[rs].lef);
	}
	int build(int le,int re)
	{
		int u=++nn;
		int mid=(le+re)/2;
		n[u].le=le;	n[u].re=re;
		n[u].len=re-le+1;
		if(le==re)	n[u].lef=n[u].rig=n[u].pos=val[le],n[u].ans=getans(val[le]);
		else
		{
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	void operate(int u,int p,double val)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(le==re)	n[u].lef=n[u].rig=n[u].pos=val,n[u].ans=getans(val);
		else
		{
			if(re<=mid)	operate(n[u].ls,p,val);
			else		operate(n[u].rs,p,val);
			pull(u);
		}
	}
	CON query(int u,int lc,int rc)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
	//	cout<<r<<" "<<u<<" "<<le<<" "<<re<<" "<<lc<<" "<<rc<<endl;
	//	getchar(); 
		if(le==lc&&re==rc)	return CON(n[u]);
		else
		{
			if(rc<=mid)	return query(n[u].ls,lc,rc);
			else
			{
				if(lc>=mid+1)	return query(n[u].rs,lc,rc);
				else	return merge(query(n[u].ls,lc,mid),query(n[u].rs,mid+1,rc));
			}
		}
	}
}xd;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>val[i];
	xd.r=xd.build(1,n);
	cout<<xd.n[xd.r].lef<<"="<<xd.n[xd.r].rig<<" "<<xd.n[xd.r].pos<<" "<<xd.n[xd.r].ans<<endl;
	for(int i=1;i<=m;i++)
	{
		int cmd,l,r,x;	double val;	cin>>cmd;
		if(cmd==0)	cin>>l>>r,cout<<xd.query(xd.r,l,r).ans<<endl;
		if(cmd==1)	cin>>x>>val,xd.operate(xd.r,x,val);
	}
}
