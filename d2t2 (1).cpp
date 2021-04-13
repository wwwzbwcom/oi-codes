#include<iostream>
#include<cstdio>
using namespace std;
long long a[100];
long long s[10000000];
int main()
{
	long long k,x,y,mod,p;
	cin>>k>>x>>y>>mod;
	p=x-y+1;
	for(int i=1;i<=k;i++)	cin>>a[i];
	s[1]=1;
	for(int i=1;i<p;i++)
	{
		int e=max(i-k+1,(long long)1);
		for(int j=i;j>=e;j--)
		{
			s[i+1]+=(s[j]*a[i-j+1])%mod;
		}
	}
	cout<<s[p];
}
