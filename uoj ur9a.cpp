#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
long long n,m,r;
bool check(long long val)
{
	long long se=sqrt(val)+1e-5;
	long long tot=val*(val-1);
	if(tot==0)	return 1;
	if(se==1||n==1)
	{
		if(tot-(val-1)*2ll<=r*2ll)	return 1;
		else	return 0;
	}
	if(se<n)
	{	
		long long lef=val-se*se;
		long long tmp=lef;
		long long cor=0;
		for(int i=1;i<=4;i++)	if(tmp>i*se)	tmp-=se,tmp--,cor++;
		if(tot-( ( ((se-2)*(se-2)*4ll) + (4*(se-2)*3ll) + (4*2ll) ) + (lef>0)*( (lef-1-cor)*4ll + (1+cor)*2ll) ) <=r*2ll)	return 1;
		else	return 0;
	}
	else
	{
		se=n;
		long long le=val/n;
		long long lef=val-se*le;
	//	cout<<tot<<" "<< ( ((se-2)*(le-2)*4ll) + (2*(se-2)*3ll) + (2*(le-2)*3ll) + (4*2ll) ) <<" "<< (lef-1)*4ll + 1*2ll <<endl;
		if(tot-( ( ((se-2)*(le-2)*4ll) + (2*(se-2)*3ll) + (2*(le-2)*3ll) + (4*2ll) ) + (lef>0)*( (lef-1)*4ll + 1*2ll ) )<=r*2ll)	return 1;
		else	return 0;
	}
}
int main()
{
	cin>>n>>m>>r;
	//cout<<check(4)<<endl;
	if(n>m)	swap(n,m);
	long long l=1,r=min((long long)2e9,n*m),ans=0;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		//cout<<l<<" "<<r<<" "<<check(mid)<<endl;
		if(check(mid))	ans=mid,l=mid+1;
		else	r=mid-1;
	}
	cout<<ans<<endl;
}
