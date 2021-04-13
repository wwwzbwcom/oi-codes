#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
map <int,int> boo;
long long a,b;
long long qsm(long long a,long long b)
{
	if(b==0)	return 1;
	else
	{
		long long ans=qsm(a,b/2);
		if(b%2==0)	return ans*ans;
		else	return ans*ans*a;
	}
}
int main()
{
	cin>>a>>b;
	for(long long i=1;i<=a;i++)
	{
		for(long long j=1;j<=b;j++)
		//	cout<<i<<" "<<j<<" "<<qsm(i,j)<<endl,
			boo[qsm(i,j)]=1;
	}
	cout<<boo.size()<<endl;
}
