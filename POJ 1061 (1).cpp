#include<iostream>
#include<cmath>
using namespace std;
long long a,b,m,n,L;
long long x,y;
long long ex_gcd(int a,int b)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	long long ans=ex_gcd(b,a%b);
	long long t=x;
	x=y;
	y=t-(a/b)*x;
	return ans;
}
int main()
{
	cin>>a>>b>>m>>n>>L;
	long long gcd=ex_gcd((n-m),L);
	if((a-b)%gcd)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	x*=(a-b)/gcd;
	cout<<(x%L+L)%L<<endl; 
}
