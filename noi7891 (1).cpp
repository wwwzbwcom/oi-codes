#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
double a,b,c,d;
double f(double x)
{
	return a*x*x*x+b*x*x+c*x+d;
}
int main()
{
	cin>>a>>b>>c>>d;
	for(double i=-100;i<=100;i+=0.01)
	{
		if(abs(f(i))<0.1)
		{
			double ans=abs(f(i));
			double p=i;
			double t=i+1;
			for(i;i<=t;i+=0.01)
				if(abs(f(i))<ans)
					ans=abs(f(i)),p=i;	
			printf("%.2f ",p);
		}
	}
}
