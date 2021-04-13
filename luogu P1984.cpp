#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	
	int n;
	cin>>n;
	
	double sum=0,now=100/(double)n;  
    for (int i=1;i<=n;i++){  
        sum+=now;  
        double j=(double)i;  
        now=now*(2*j-1)/(2*j);
    }  
    cout<<sum<<endl;
	
	
	double ans=0;
	double tem=0;
	double num=n;
	for(double i=num;i>=1;i--)
	{
	//	cout<<tem<<" "<<(4200.0*(100.0-tem))/num<<endl;
		ans+=((100.0-tem))/num;
		tem=(tem*(i-1)+100.0)/i;
	}
	
	printf("%.2lf\n",ans);
}
