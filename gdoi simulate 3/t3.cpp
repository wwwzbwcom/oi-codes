#include<iostream>
#include<cstdio>
using namespace std;
long long gn;
long long n,m,k,p;
long long ans;
long long nc,mc;
long long rev[10000];
long long qsm(long long a,long long b)
{
	if(b==0)	return 1;
	else
	{
		long long ans=qsm(a,b/2);
		ans=(ans*ans)%p;
		if(b%2==1)	return (ans*a)%p;
		else	return ans;
	}
}
int C(int a,int b)
{
	int ans=1;
	for(int i=b+1;i<=a;i++)	ans=(ans*i)%p;
	for(int i=1;i<=a-b;i++)	ans=(ans*rev[i])%p;
	return ans;
}
int main()
{
//	freopen("luckye.in","r",stdin);
//	freopen("luckye.out","w",stdout);
	cin>>gn;
	for(long long g=1;g<=gn;g++)
	{
		cin>>n>>m>>k>>p;
		ans=0;
		for(int i=1;i<10000;i++)	rev[i]=qsm(i,p-2);
		for(int i=0;i<=k/2;i++)
		{
			//if(g==2&&i>5000)
		//	cout<<i<<endl;
			mc=i;
			nc=k-mc*2;
			if(n==0&&nc!=0)	continue;
			if(m==0&&mc!=0)	continue;
			
			if(n==0)	ans=(ans+C(m+mc-1,mc))%p;
			if(m==0)	ans=(ans+C(n+nc-1,nc))%p;
			if(n!=0&&m!=0)	ans=(ans+C(n+nc-1,nc)*C(m+mc-1,mc))%p;
		}
		cout<<ans<<endl; 
	}
}
