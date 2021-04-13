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
		int xo=x,yo=y;
		x=yo;
		y=xo-(a/b)*x;
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
		x=((x*(b/d))%c+c)%c;
		return x%(c/d);
	}
	else	return -1;
}
int main()
{
	int a,b,c;	cin>>a>>b>>c;
	cout<<work(a,b,c)<<endl;
}
