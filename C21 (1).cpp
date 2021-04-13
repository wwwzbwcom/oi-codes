#include<iostream>
using namespace std;
double t,s,q;
int cnt=0,ans=0;
int main()
{
	cin>>t>>s>>q;
	double cur=0;
	double c=s;
	double sn=s;
	while(cur<t)
	{
		cur+=c;
		sn+=c*q;
		c=c*((q-1)/q);
		cout<<sn<<" "<<cur<<" "<<c<<endl;
		if(sn>cur) sn=0,cnt++;
	}
	cout<<cnt<<endl;
}
