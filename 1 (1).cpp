#include<iostream>
using namespace std; 
int main()
{
	int n;
	cin>>n;
	long long ans=(((((n*(n+1))%10007)*(2*n+1))%10007)*3336)%10007;
	cout<<ans<<endl;
}
