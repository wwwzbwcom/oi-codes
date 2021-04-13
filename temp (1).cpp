#include<iostream>
#include<map> 
using namespace std;
const long long mod=1e9+9;
int main()
{
	for(long long i=1;i<=mod;i++)
	{
		if((133*i)%mod==1)	cout<<i<<endl;
	}
}
