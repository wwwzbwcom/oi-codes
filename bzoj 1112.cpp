#include<algorithm>
#include<cstdio>
using namespace std;
struct Splay
{
	struct Node
	{
		int ls,rs;
		int val,cnt;
		long long sum;
	}n[100100];
	int nn;
	int ro;
	void pull(int u)
	{
		n[0].ls=n[0].rs=0;
		n[0].val=n[0].sum=n[0].cnt=0;
		n[u].sum=n[n[u].ls].sum+n[n[u].rs].sum+n[u].val;
		n[u].cnt=n[n[u].ls].cnt+n[n[u].rs].cnt+1;
		n[0].ls=n[0].rs=0;
		n[0].val=n[0].sum=n[0].cnt=0;
	}
	void lrotate(int &u)
	{
		int rs=n[u].rs;	n[u].rs=n[rs].ls;	n[rs].ls=u;	pull(u);	pull(rs);	u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;	n[u].ls=n[ls].rs;	n[ls].rs=u;	pull(u);	pull(ls);	u=ls;
	}
	void insert(int &u,int val)
	{
		if(u==0)
		{
			u=++nn;
			n[u].cnt=1;
			n[u].val=n[u].sum=val;
			n[u].ls=n[u].rs=0;
		}
		else
		{
			if(val<=n[u].val)
			{
				if(n[u].ls!=0&&val<=n[n[u].ls].val)	rrotate(u);
				insert(n[u].ls,val);rrotate(u);
			}
			else
			{
				if(n[u].rs!=0&&val>n[n[u].rs].val)	lrotate(u);
				insert(n[u].rs,val);lrotate(u);
			}
		}
	}
	void findkth(int &u,int k)
	{
	//	if(u==0)	while(1);
		if(k==n[n[u].ls].cnt+1)	return;
		else
		{
			if(k<n[n[u].ls].cnt+1)
			{
				if(n[u].ls!=0&&k<n[n[n[u].ls].ls].cnt+1)	rrotate(u);
				findkth(n[u].ls,k);rrotate(u);
			}
			else
			{
				if(n[u].rs!=0&&k-n[n[u].ls].cnt-1>n[n[n[u].rs].ls].cnt+1)	lrotate(u);
				findkth(n[u].rs,k-n[n[u].ls].cnt-1);lrotate(u);
			}
		}
	}
	void findval(int &u,int val)
	{
	//	if(u==0)	while(1);
		if(val==n[u].val)	return;
		else
		{
			if(val<n[u].val)
			{
				if(n[u].ls!=0&&val<n[n[u].ls].val)	rrotate(u);
				findval(n[u].ls,val);rrotate(u);
			}
			else
			{
				if(n[u].rs!=0&&val>n[n[u].rs].val)	lrotate(u);
				findval(n[u].rs,val),lrotate(u);
			}
		}
	}
	void goright(int &u)
	{
	//	if(u==0)	while(1);
		if(n[u].rs==0)	return;
		else
		{
			if(n[n[u].rs].rs!=0)	lrotate(u);
			goright(n[u].rs);lrotate(u);
		}
	}
	void erase(int k)
	{
		findkth(ro,k);
		if(n[ro].ls)
		{
			goright(n[ro].ls);
			n[n[ro].ls].rs=n[ro].rs;
			ro=n[ro].ls;
			pull(ro);
		}
		else	ro=n[ro].rs;
	}
	long long getans()
	{
		return ((long long)n[ro].val*n[n[ro].ls].cnt-(long long)n[n[ro].ls].sum)+((long long)n[n[ro].rs].sum-(long long)n[ro].val*n[n[ro].rs].cnt);
	}
}sp;
int n,k;
int sto[100100];
long long ans=1e18;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	for(int i=1;i<=k;i++)	sp.insert(sp.ro,sto[i]);
	
	if(k%2==0)	sp.findkth(sp.ro,k/2);	else	sp.findkth(sp.ro,k/2+1);
	ans=min(ans,sp.getans());
	for(int i=k+1;i<=n;i++)
	{
		sp.findval(sp.ro,sto[i-k]);
		int kth=sp.n[sp.n[sp.ro].ls].cnt+1;
		sp.erase(kth);
		sp.insert(sp.ro,sto[i]);
		if(k%2==0)	sp.findkth(sp.ro,k/2);	else	sp.findkth(sp.ro,k/2+1); 
		ans=min(ans,sp.getans());
	}
	printf("%lld\n",ans);
}
