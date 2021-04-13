#include<iostream>
using namespace std;
int pt()
{
	for(int i=2;i<=1e6;i++)
	{
		if(book[i]==0)	prime[cnt++]=i;
			
		for(int j=0;j<cnt;j++)
		{
			if(prime[j]*i>1e6)	break;
			book[prime[j]*i]=1;
			if(i%prime[j]==0)	break;
		}
	}
}
int main()
{
	int n,k;
	cin>>n>>k;
	cout<<n/k<<endl;
}
