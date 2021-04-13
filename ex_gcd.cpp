#include<iostream>
using namespace std;
int ex_gcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;	y=0;
		return a;
	}
	int	t=ex_gcd(b,a%b,x,y);
	int xn=x,yn=y;
	x=yn;
	y=(xn-(a/b)*yn);
	return t;
}
int main()
{
	int a,b,x,y;
	cin>>a>>b;
	int gcd=ex_gcd(a,b,x,y);
	cout<<gcd<<" "<<x<<" "<<y<<endl;
}
