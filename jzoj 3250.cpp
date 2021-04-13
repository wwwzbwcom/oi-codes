#include<iostream>
using namespace std;
int gn,n,p;
int sto[30];
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=((long long)ans*ans)%(long long)p;
		if(b%2==0)	return ans;
		else	return ((long long)ans*a)%(long long)p;
	}
}
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n>>p;
		for(int i=1;i<=n;i++)	cin>>sto[i];
		int cur=sto[n];
		for(int i=n-1;i>=1;i--)	cur=qsm(sto[i],cur),cout<<cur<<endl;
		cout<<cur<<endl;
	}
}
