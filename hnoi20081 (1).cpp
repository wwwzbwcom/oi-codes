#include<iostream>
using namespace std;
const long long mod=100003;
long long ksm(long long a,long long b)
{
	if(b==0) return 1;
	long long ans=ksm(a,b/2)%mod;
	ans=(ans*ans)%mod;
	if(b%2==1) return (ans*a)%mod;
	else return ans%mod;
}
long long n,m;
int main()
{
	cin>>n>>m;
	cout<<((ksm(n,m)-ksm(n-1,m-1)*n)%mod+mod)%mod<<endl;
}
