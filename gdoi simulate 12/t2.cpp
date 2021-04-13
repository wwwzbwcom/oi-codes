#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
const int mod1=1e9+7;
const int mod2=1e8+7;
const int mod3=1e7+7;
map <int,map<int,map<int,int> > > boo;
int a,b;
int qsm1(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm1(a,b/2);
		ans=(ans*(long long)ans)%(long long)mod1;
		if(b%2==0)	return ans;
		else	return (ans*(long long)a)%(long long)mod1;
	}
}
int qsm2(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm2(a,b/2);
		ans=(ans*(long long)ans)%(long long)mod2;
		if(b%2==0)	return ans;
		else	return (ans*(long long)a)%(long long)mod2;
	}
}
int qsm3(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm3(a,b/2);
		ans=(ans*(long long)ans)%(long long)mod3;
		if(b%2==0)	return ans;
		else	return (ans*(long long)a)%(long long)mod3;
	}
}
int main()
{
	cin>>a>>b;
	for(long long i=1;i<=a;i++)
	{
		for(long long j=1;j<=b;j++)
			boo[qsm1(i,j)][qsm2(i,j)][qsm3(i,j)]=1;
	}
	cout<<boo.size()<<endl;
}
