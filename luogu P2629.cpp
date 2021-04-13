#include<iostream>
using namespace std;
int n;
int sum[1000000];
struct XDS
{
	struct Point
	{
		int ls,rs;
		int le,re;
		int min0;
	}p[2000000];
	int pn;
	int build(int l,int r)
	{
		int now=pn++;
		p[now].le=l;p[now].re=r;
		if(l==r)
		{
			p[now].ls=p[now].rs=-1;
			p[now].min0=sum[l];
		}
		else
		{
			p[now].ls=build(l,(l+r)/2);
			p[now].rs=build((l+r)/2+1,r);
			p[now].min0=min(p[p[now].ls].min0,p[p[now].rs].min0);
		}
		return now;
	}
	int query(int now,int l,int r)
	{
		int le=p[now].le,re=p[now].re;
		int mid=(le+re)/2;
		if(l==le&&r==re)	return p[now].min0;
		
		if(r<=mid)	return	query(p[now].ls,l,r);
		else	if(l>=mid+1)	return	query(p[now].rs,l,r);
		else	return min(query(p[now].ls,l,mid),query(p[now].rs,mid+1,r));
	}
}x;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>sum[i];
	sum[0]=0;
	for(int i=1;i<=n;i++)	sum[i]=sum[i-1]+sum[i];
	int root=x.build(1,n);
//	cout<<"========="<<endl;
//	cout<<x.query(root,3,n-1)<<endl;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int min1=x.query(root,i,n);
		int min2;
		if(i>1)	min2=x.query(root,1,i-1);
		else	min2=0;
		if(min1-sum[i-1]>=0&&min2+sum[n]-sum[i-1]>=0)	ans++;
	//	cout<<min1<<" "<<sum[i-1]<<" "<<min2<<" "<<sum[n]-sum[i-1]<<" "<<ans<<endl;
	}
	cout<<ans<<endl;
}
