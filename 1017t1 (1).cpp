#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int gn;
	cin>>gn;
	while(gn--)
	{
		int n;
		double a,b,c;
		cin>>n;
		if(n==1)
		{
			cin>>b>>a;
			double x=(-b)/a;
			if(abs(x-(double)((int)x))<1e-6)	cout<<"Yes"<<endl;
			else cout<<"No"<<endl; 
		}
		if(n==2)
		{
			cin>>c>>b>>a;
			double delta=b*b-4*a*c;
			double x1=(-b+sqrt(delta))/(2*a);
			double x2=(-b-sqrt(delta))/(2*a);
			if(abs(x1-(double)((int)x1))<1e-6	||	abs(x2-(double)((int)x2))<1e-6)	cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
}
