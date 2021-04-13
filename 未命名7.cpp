#include<iostream>
using namespace std;
int main()
{
	double ans=0,mul1=4,mul2=1;
	for(int i=1;i<=100;i++)
	{
		ans+=(mul2*i/mul1);
		mul1*=4;
		mul2*=3;
	} 
	cout<<ans;
}
