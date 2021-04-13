#include<iostream>
using namespace std;
long long n,k,ans;
int main()
{
	cin>>n>>k;
	for(long long i=1;i<=min(n,k);)
	{
		long long las=k/(k/i);
		las=min(las,min(n,k));
		ans+=k*(las-i+1)-((i+las)*(las-i+1)/2)*(k/i);
		i=las+1;
	}
	if(n>k)	ans+=(n-k)*k;
	cout<<ans<<endl;
} 
