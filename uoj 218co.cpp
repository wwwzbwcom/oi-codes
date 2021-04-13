#include<iostream>
using namespace std;
const int maxn=500100;
int n,m,ty;
int ans;
struct XDS
{
	struct NODE
	{
		int ls,rs;
		int le,re;
		int set,sum;
	}n[maxn*2];
	int nn,r;
	void push(int u)
	{
		if(n[u].set!=-1)	n[n[u].ls].set=n[n[u].rs].set=n[u].set,n[u].set=-1,n[u].sum=0;
		pull(u);
	}
	void pull(int u)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
		if(le!=re)
		{
			n[u].sum=0;
			if(n[n[u].ls].set!=-1)	n[u].sum+=n[n[u].ls].set*(mid-le+1);
			else					n[u].sum+=n[n[u].ls].sum;
			
			if(n[n[u].rs].set!=-1)	n[u].sum+=n[n[u].rs].set*(re-(mid+1)+1);
			else					n[u].sum+=n[n[u].rs].sum;
		}
	}
	int build(int le,int re)
	{
		int u=++nn;
		int mid=(le+re)>>1;
		n[u].le=le;	n[u].re=re;
		n[u].set=-1;	n[u].sum=0;
		if(le!=re)
		{
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	int setrng(int u,int lc,int rc,int x)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
	//	cout<<u<<" "<<le<<"="<<re<<" "<<lc<<"="<<rc<<endl;
	//	getchar();
		if(le==lc&&re==rc)	n[u].set=x;
		else
		{
			push(u);
			if(rc<=mid)	setrng(n[u].ls,lc,rc,x);
			else
			{
				if(lc>=mid+1)	setrng(n[u].rs,lc,rc,x);
				else	setrng(n[u].ls,lc,mid,x),setrng(n[u].rs,mid+1,rc,x);
			}
			pull(u);
		}
	}
	int sumrng(int u,int lc,int rc)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
		if(le==lc&&re==rc)
		{
		//	cout<<le<<"="<<re<<" "<<n[u].set<<" "<<n[u].sum<<endl;
			if(n[u].set!=-1)	return n[u].set*(re-le+1);
			else				return n[u].sum;
		}
		else
		{
			push(u);
			int ans=0;
			if(rc<=mid)	ans=sumrng(n[u].ls,lc,rc);
			else
			{
				if(lc>=mid+1)	ans=sumrng(n[u].rs,lc,rc);
				else	ans=sumrng(n[u].ls,lc,mid)+sumrng(n[u].rs,mid+1,rc);
			}
			pull(u);
			return ans;
		}
	}
}xd;
struct KCJ
{
	struct NODE
	{
		int ls,rs;
		int le,re;
		int set,tim;
	}n[maxn*20];
	int nn,r[maxn],rn;
	void push(int u)
	{
		if(n[u].set!=-1)
		{
			n[n[u].ls].set=n[n[u].rs].set=n[u].set;
			n[n[u].ls].tim=n[n[u].rs].tim=n[u].tim;
			n[u].set=n[u].tim=-1;
		}
	}
	int build(int le,int re)
	{
	//	if(xd.n[250002].le==-1)	cout<<le<<"="<<re<<" "<<xd.n[250002].le<<"=="<<xd.n[250002].re<<endl,getchar();
		int u=++nn;
		int mid=(le+re)>>1;
		n[u].le=le;	n[u].re=re;
		n[u].set=-1;n[u].tim=-1;
		if(le!=re)
		{
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	int setrng(int u,int lc,int rc,int set,int tim)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
		if(le==lc&&re==rc)	n[u].set=set,n[u].tim=tim;
		else
		{
			int t;
			t=++nn;	n[t]=n[n[u].ls];	n[u].ls=t;
			t=++nn;	n[t]=n[n[u].rs];	n[u].rs=t;
			push(u);
			if(rc<=mid)	setrng(n[u].ls,lc,rc,set,tim);
			else
			{
				if(lc>=mid+1)	setrng(n[u].rs,lc,rc,set,tim);
				else	setrng(n[u].ls,lc,mid,set,tim),setrng(n[u].rs,mid+1,rc,set,tim);
			}
		}
	}
	pair <int,int> qrypos(int u,int pos)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)>>1;
		if(le==re)	return make_pair(n[u].set,n[u].tim);
		else
		{
			push(u);
			if(pos<=mid)	return qrypos(n[u].ls,pos);
			else			return qrypos(n[u].rs,pos);
		}
	}
}cj;
void query(int l,int r)
{
	if(l>r)	swap(l,r);
	ans=xd.sumrng(xd.r,l,r);
	cout<<ans<<endl;
}
void pop(int l)
{
	 
	pair <int,int> ans;
	
	ans=cj.qrypos(cj.r[cj.rn],l);
	if(ans.second-1>=0)	ans=cj.qrypos(cj.r[ans.second-1],l);
	else	ans=make_pair(-1,-1);
	
	cj.rn++;
	cj.r[cj.rn]=++cj.nn;
	cj.n[cj.r[cj.rn]]=cj.n[cj.r[cj.rn-1]];
	cj.setrng(cj.r[cj.rn],l,l,ans.first,ans.second);
	
	
	
	xd.setrng(xd.r,l,l,ans.first);
//	cout<<"===="<<endl;
}
void insert(int l,int r,int x)
{
	if(l>r)	swap(l,r);
	
//	cout<<l<<"="<<r<<endl; 
	
	cj.rn++;
	cj.r[cj.rn]=++cj.nn;
	cj.n[cj.r[cj.rn]]=cj.n[cj.r[cj.rn-1]];
	cj.setrng(cj.r[cj.rn],l,r,x,cj.rn);
	
	xd.setrng(xd.r,l,r,x);
}
int main()
{
	freopen("ex_C3.in","r",stdin);
	freopen("out.txt","w",stdout);
	cin>>n>>m>>ty;
	xd.r=xd.build(1,n);
	cj.r[0]=cj.build(1,n);
	
	for(int i=1;i<=m;i++)
	{
		cout<<i<<endl;
		int cmd,l,r,x;
		cin>>cmd;
		if(cmd==1)	cin>>l>>r	,l=(l+ans*ty)%n+1,r=(r+ans*ty)%n+1,query(l,r); 
		if(cmd==2)	cin>>l		,l=(l+ans*ty)%n+1				  ,pop(l);
		if(cmd==3)	cin>>l>>r>>x,l=(l+ans*ty)%n+1,r=(r+ans*ty)%n+1,insert(l,r,x);
	}
}
