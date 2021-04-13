#include<iostream>
using namespace std;
int gcd(int a,int b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
void ex_gcd(int a,int b,int &x,int &y)
{
	if(b==0)	x=1,y=0;
	else
	{
		ex_gcd(b,a%b,x,y);
		int x0=x,y0=y;
		x=y0;
		y=x0-(a/b)*x;
	}
}
int work(int a,int b,int c)
{
	a=(a%c+c)%c;	b=(b%c+c)%c;
	int d=gcd(a,c);
	if(b%d==0)
	{
		int x,y;
		ex_gcd(a,c,x,y);
		int mod=(c/d);
		x=((x*(b/d))%mod+mod)%mod;
		return x;
	}
	else	return -1;
}
int main()
{
	int a,b,c;	cin>>a>>b>>c;
	cout<<work(a,b,c)<<endl;
}
