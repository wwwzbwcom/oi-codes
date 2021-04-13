#include<cstdio>
#include<iostream>
using namespace std;
long long gn;
long long n,l,r;
int main()
{
//	cout<<(1<<10)<<endl;
	scanf("%lld",&gn);
	for(long long g=1;g<=gn;g++)
	{
		scanf("%lld%lld%lld",&n,&l,&r);
		long long ans;
		if(n==1)	ans=r-l+1;
		else
		{
			long long p,ml,mm;
			for(long long i=1;r-(1ll<<i)>=0;i++)	p=i;
			if(l-(1ll<<p)>=0)	ans=r-l+1;
			else
			{
				ml=(1ll<<p)|l;	mm=(1ll<<(p+1))-1;
				cout<<r-l+1<<"="<<ml<<"="<<mm<<" "<<r<<" "<<(1ll<<p)<<" "<<endl;
				if(ml>r)	cout<<"1="<<endl,ans=(r-l+1)+(mm-ml+1)*(r-(1<<p)+1);
				else	cout<<"2="<<endl,ans=mm-l+1;
			}
		}
		printf("%lld\n",ans);
	}
}
