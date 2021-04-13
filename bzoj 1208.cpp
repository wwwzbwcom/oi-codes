#include<algorithm>
#include<cstdio>
using namespace std;
const long long oo=1e15;
const long long mod=1e6;
struct Splay
{
	struct Node
	{
		long long ls,rs;
		long long val,exi;
		long long cnt,mni,mxa;
	}n[100000];
	long long nn,root;
	long long size()
	{
		return n[root].cnt;
	}
	void upload(long long u)
	{
		n[u].cnt=n[n[u].ls].cnt+n[n[u].rs].cnt+n[u].exi;
		
		n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
		n[u].mxa=max(n[n[u].ls].mxa,n[n[u].rs].mxa);
		
		if(n[u].exi==1)	n[u].mni=min(n[u].mni,n[u].val),n[u].mxa=max(n[u].mxa,n[u].val);
	}
	void lrotate(long long &u)
	{
		long long rs=n[u].rs;n[u].rs=n[rs].ls;n[rs].ls=u;upload(u);upload(rs);u=rs;
	}
	void rrotate(long long &u)
	{
		long long ls=n[u].ls;n[u].ls=n[ls].rs;n[ls].rs=u;upload(u);upload(ls);u=ls;
	}
	void insert(long long &u,long long val)
	{
		if(u==0)
		{
			u=++nn;
			n[u].val=n[u].mni=n[u].mxa=val;
			n[u].exi=n[u].cnt=1;
		}
		else
		{
			if(val<n[u].val)	insert(n[u].ls,val),rrotate(u);
			else	insert(n[u].rs,val),lrotate(u); 
		}
	}
	long long findlas(long long &u,long long val)
	{	
		if(val==n[u].val&&n[u].exi==1)	return val;
		else
		{
			long long t=-1e15;
			if(val<n[u].val)
			{
				if(n[u].ls!=0) t=findlas(n[u].ls,val),rrotate(u);
			}
			else
			{
				if(n[u].exi==1)	t=n[u].val;
				if(n[n[u].rs].mni<=val)
				{
					if(n[u].rs!=0)	t=max(t,findlas(n[u].rs,val)),lrotate(u);
				}
				else
				{
					if(n[u].ls!=0)	t=max(t,findlas(n[u].ls,val)),rrotate(u);
				}
			}
			return t;
		}
	}
	long long findnxt(long long &u,long long val)
	{
		if(val==n[u].val&&n[u].exi==1)	return val;
		else
		{
			long long t=1e15;
			if(val<n[u].val)
			{
				if(n[u].exi==1)	t=n[u].val;
				if(n[n[u].ls].mxa>=val)
				{
					if(n[u].ls!=0)	t=min(t,findnxt(n[u].ls,val)),rrotate(u);
				}
				else
				{
					if(n[u].rs!=0)	t=min(t,findnxt(n[u].rs,val)),lrotate(u);
				}
			}
			else
			{
				if(n[u].rs!=0)	t=findnxt(n[u].rs,val),lrotate(u);
			}
			return t;
		}
	}
	void erase(long long &u,long long val)
	{	
		if(val==n[u].val)
		{
			n[u].exi=0;
			return;
		}
		if(val<n[u].val)	erase(n[u].ls,val),rrotate(u);
		else	erase(n[u].rs,val),lrotate(u);
	}
}sp0,sp1;
long long n;
long long ans=0;
int main()
{
	scanf("%lld",&n);
	sp0.insert(sp0.root,-oo);	sp0.insert(sp0.root,oo);
	sp1.insert(sp1.root,-oo);	sp1.insert(sp1.root,oo);
	for(long long i=1;i<=n;i++)
	{
		long long a,b;scanf("%lld%lld",&a,&b);
		if(a==0)
		{
			if(sp1.size()==2)	sp0.insert(sp0.root,b);
			else
			{
				long long las=sp1.findlas(sp1.root,b),nxt=sp1.findnxt(sp1.root,b);
				if(abs(b-las)<=abs(b-nxt))	sp1.erase(sp1.root,las),ans+=abs(b-las);
				else	sp1.erase(sp1.root,nxt),ans+=abs(b-nxt);
			}
		}
		else
		{
			if(sp0.size()==2)	sp1.insert(sp1.root,b);
			else
			{
				long long las=sp0.findlas(sp0.root,b),nxt=sp0.findnxt(sp0.root,b);
				if(abs(b-las)<=abs(b-nxt))	sp0.erase(sp0.root,las),ans+=abs(b-las);
				else	sp0.erase(sp0.root,nxt),ans+=abs(b-nxt);
			}	
		}
		ans%=mod;
	}
	printf("%lld\n",ans);
}
