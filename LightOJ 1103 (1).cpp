#include<iostream>
using namespace std;
int gn,n;
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n;
		double cur=0;
		if(n==1) cout<<"Case "<<g<<": "<<1<<endl; 
		for(int i=1;i<=n;i++)
		{
			if(cur>=0.5)
			{
				cout<<"Case "<<g<<": "<<i-1<<endl;
				break;
			}
			cur+=(1.0-cur)*(((double)i)/((double)n));
		}
	}
}
