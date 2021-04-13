#include<iostream>
#include<cstdio>
using namespace std;
int n;
int s[3000000];
int lmax[3000000];
int rmax[3000000];
int main()
{
	scanf("%d",&n);
//	for(int i=1;i<=n;i++)	scanf("%d",&s[i]);
	cout<<"========"<<endl;
	lmax[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(s[i-1]>=s[i])	lmax[i]=lmax[i-1]+1;
		else lmax[i]=1;
	}
	lmax[n]=1;
	for(int i=n-1;i>=1;i--)
	{
		if(s[i+1]>=s[i])	rmax[i]=rmax[i+1]+1;
		else rmax[i]=1;
	}
	cout<<"======="<<endl;
	for(int i=1;i<=n;i++)	cout<<lmax[i]<<" "<<rmax[i]<<endl;
	long long ans=0;
	for(int i=1;i<=n;i++)	ans=max(ans,(long long)s[i]*(rmax[i]+lmax[i]-1));
//	printf("%lld",ans);
}
