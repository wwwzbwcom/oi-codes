#include "kth.h"
int an,bn,cn;
int calca(int val)
{
	int l=0,r=an,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
	//	cout<<l<<" "<<mid<<" "<<r<<endl;
		if(get_a(mid)<=val)	l=mid+1,ans=mid;
		else	r=mid-1;
	}
	return ans+1;
}
int calcb(int val)
{
	int l=0,r=bn,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(get_b(mid)<=val)	l=mid+1,ans=mid;
		else	r=mid-1;
	}
	return ans+1;
}
int calcc(int val)
{
	int l=0,r=cn,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(get_c(mid)<=val)	l=mid+1,ans=mid;
		else	r=mid-1;
	}
	return ans+1;
}
int query_kth(int ai,int bi,int ci,int k)
{
	an=ai;	bn=bi;	cn=ci;
	//cout<<calca(1)<<"============"<<endl;
	//return 0;
	int l=0,r=1e9,ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
	//	cout<<mid<<" "<<calca(mid)<<" "<<calcb(mid)<<" "<<calcc(mid)<<endl; 
		if(calca(mid)+calcb(mid)+calcc(mid)>=k)	r=mid-1,ans=mid;
		else			l=mid+1;
	}
	return ans;
}
