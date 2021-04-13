#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
bool mark[100100];
bool book[100000];
long long prime[100000];
long long cnt=0;
void pt()
{
	for(long long i=2;i<70000;i++)
	{
		if(book[i]==0)
		{
			prime[cnt++]=i;
			for(long long j=2;j*i<70000;j++) book[i*j]=1;
		}
	}
}
long long gn;
int main()
{
	pt();
	scanf("%lld",&gn);
	for(int g=1;g<=gn;g++)
	{
		long long s,e;
		scanf("%lld%lld",&s,&e);
		memset(mark,0,sizeof mark);
		for(long long i=0;i<cnt&&prime[i]<=e;i++)
			for(int j=max((s/prime[i]),(long long)2);j*prime[i]<=e;j++)
				if(s<=j*prime[i]&&j*prime[i]<=e)
				//	cout<<j*prime[i]-s<<endl,
					mark[j*prime[i]-s]=1;
		long long ans=0;
		for(int i=max(s,(long long)2);i<=e;i++)
			if(mark[i-s]==0) ans++;
		printf("Case %lld: %lld\n",g,ans);
	}
}
