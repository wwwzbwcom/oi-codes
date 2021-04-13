#include<iostream>
using namespace std;
int f[1000100];
int main()
{
	f[1]=1;f[2]=1;
	for(int i=3;i<=1000010;i++)	f[i]=(f[i-2]+f[i-1])%1000;
	int gn;	cin>>gn;
	while(gn--)
	{
		int n;	cin>>n;
		cout<<f[n]<<endl;
	}
}
