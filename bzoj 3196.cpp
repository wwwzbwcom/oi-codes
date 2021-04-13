#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int sto[1000000];
struct Block
{
	struct Node
	{
		int l,r;
		int y[1000];
	}n[1000];
	int nn;
	int bl;
	void build(int tl)
	{
		bl=sqrt(tl);
		int cur=0;
		n[nn].l=1;
		for(int i=1;i<tl;i++)
		{
			n[nn].y[cur]=sto[i];
			cur++;
			if(cur==bl)	sort(n[nn].y,n[nn].y+cur),cur=0,n[nn].r=i,nn++,n[nn].l=i+1;
		}
		n[nn].y[cur]=sto[tl];
		cur++;
		sort(n[nn].y,n[nn].y+cur),cur=0,n[nn].r=tl,nn++;
	}
	int getkth(int l,int r,int k)
	{
		int ans=0;
		if(r-l+1<=bl)
		{
			for(int j=l;j<=r;j++)	if(sto[j]<k)	ans++;
			return ans;
		}
		for(int i=0;i<nn;i++)
		{ 
			if(l> n[i].l&&l<=n[i].r)	for(int j=l;j<=n[i].r;j++)	if(sto[j]<k)	ans++;
			if(l<=n[i].l&&n[i].r<=r)	ans+=lower_bound(n[i].y,n[i].y+(n[i].r-n[i].l+1),k)-n[i].y;
			if(r>=n[i].l&&r< n[i].r)	for(int j=n[i].l;j<=r;j++)	if(sto[j]<k)	ans++;
		}
		return ans+1;
	}
	int findkth(int lc,int rc,int k)
	{
		int l=0,r=2e8,ans;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(getkth(lc,rc,mid)>k)	r=mid-1;
			else	ans=mid,l=mid+1;
		}
		return ans;
	}
	void change(int pos,int k)
	{
		sto[pos]=k;
		for(int i=0;i<nn;i++)
			if(n[i].l<=pos&&pos<=n[i].r)
			{
				for(int j=n[i].l;j<=n[i].r;j++)
				{
					n[i].y[j-n[i].l]=sto[j];
				}
				sort(n[i].y,n[i].y+(n[i].r-n[i].l+1));
			}
	}
	int findpre(int l,int r,int k)
	{
		int ans=-2e8;
		if(r-l+1<=bl)
		{
			for(int j=l;j<=r;j++)	if(sto[j]<k)	ans=max(ans,sto[j]);
			return ans;
		}
		for(int i=0;i<nn;i++)
		{
			if(l> n[i].l&&l<=n[i].r)	for(int j=l;j<=n[i].r;j++)	if(sto[j]<k)	ans=max(ans,sto[j]);
			if(l<=n[i].l&&n[i].r<=r)
			{
				int pos=lower_bound(n[i].y,n[i].y+(n[i].r-n[i].l+1),k)-n[i].y;
				if(pos>=1&&n[i].y[pos-1]<k)	ans=max(ans,n[i].y[pos-1]);
			}
			if(r>=n[i].l&&r< n[i].r)	for(int j=n[i].l;j<=r;j++)	if(sto[j]<k)	ans=max(ans,sto[j]);
		}
		return ans;
	}
	int findnxt(int l,int r,int k)
	{
		int ans=2e8;
		if(r-l+1<=bl)
		{
			for(int j=l;j<=r;j++)	if(sto[j]>k)	ans=min(ans,sto[j]);
			return ans;
		}
		for(int i=0;i<nn;i++)
		{
			if(l> n[i].l&&l<=n[i].r)	for(int j=l;j<=n[i].r;j++)	if(sto[j]>k)	ans=min(ans,sto[j]);
			if(l<=n[i].l&&n[i].r<=r)
			{
				int pos=upper_bound(n[i].y,n[i].y+(n[i].r-n[i].l+1),k)-n[i].y;
				if(n[i].y[pos]>k)	ans=min(ans,n[i].y[pos]);
			}
			if(r>=n[i].l&&r< n[i].r)	for(int j=n[i].l;j<=r;j++)	if(sto[j]>k)	ans=min(ans,sto[j]);
		}
		return ans;
	}
}b;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	b.build(n);
	for(int i=1;i<=m;i++)
	{
		int cmd,l,r,k,pos;	scanf("%d",&cmd);
		if(cmd==1)	scanf("%d%d%d",&l,&r,&k),printf("%d\n",b.getkth(l,r,k));
		if(cmd==2)	scanf("%d%d%d",&l,&r,&k),printf("%d\n",b.findkth(l,r,k));
		if(cmd==3)	scanf("%d%d",&pos,&k),b.change(pos,k);
		if(cmd==4)	scanf("%d%d%d",&l,&r,&k),printf("%d\n",b.findpre(l,r,k));
		if(cmd==5)	scanf("%d%d%d",&l,&r,&k),printf("%d\n",b.findnxt(l,r,k));
	}
}
