#include<iostream>
using namespace std;
double ans=0;
int main()
{
	double mul1=4,mul2=7;
	for(int i=1;i<=100;i++)
	{
		ans+=(mul1/mul2)*i;
		mul1*=3;
		mul2*=7;
	}
	cout<<ans<<endl;
}
