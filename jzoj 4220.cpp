#include<iostream>
using namespace std;
long long k,n,m,p;
long long mul(long long a,long long b)
{
	a%=p;	b%=p;
	long long val=1e6;
	long long a1=a/val,a2=a%val;
	long long b1=b/val,b2=b%val;
	long long ans=0;
	ans+=(((a1*b1)%p*val)%p*val)%p;	ans%=p;
	ans+=((a1*b2)%p*val)%p;	ans%=p;
	ans+=((a2*b1)%p*val)%p;	ans%=p;
	ans+=(a2*b2)%p;	ans%=p;
	return ans;
}
long long qsm(long long a,long long b)
{
	if(b==0)	return 1;
	else
	{
		long long ans=qsm(a,b/2);
		ans=mul(ans,ans);
		if(b%2==0)	return ans;
		else	return mul(ans,a);
	}
}
int main()
{
	cin>>k>>n>>m>>p;
	long long ans=0;
	for(long long i=m;i<=n;i++)	ans=(ans+qsm(i,k))%p;
	cout<<ans;
}
