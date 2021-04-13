#include<iostream>
using namespace std;
const long long mod=1e9+7;
long long n,m,r,c,s;
long long ans=0;
long long ksm(int a,int b)
{
	if(b==1)	return a%mod;
	else
	{
		long long tmp=ksm(a,b/2)%mod;
		tmp=(tmp*tmp)%mod;
		if(b%2==0)	return tmp;
		else	return (tmp*a)%mod;	
	}
}
long long C(int a,int b)
{
	if(b>a)	return 0;
	long long ans=1;
	for(int i=b+1;i<=a;i++)	ans*=i,ans%=mod;
	for(int i=1;i<=a-b;i++)	ans*=ksm(i,mod-2),ans%=mod;
	return ans;
}
int main()
{
	cin>>n>>m>>r>>c>>s;
	for(long long i=0;i<=r&&i<=n;i++)	if((r-i)%2==0)
	{
		long long j=-1;
	//	cout<<(s-(i*m))<<" "<<(n-2*i)<<endl;
		if((n-2*i)!=0&&(s-(i*m))%(n-2*i)==0)	j=(s-(i*m))/(n-2*i);//cout<<"==="<<endl;
		if(j>0&&j<=c&&j<=m&&(c-j)%2==0)
		{
			long long cur=(C(n,i)*C(m,j))%mod;
		//	cout<<cur<<endl;
			if(n-1>=0)	cur=(cur*C(n+(r-i)/2-1,n-1))%mod;
			if(m-1>=0)	cur=(cur*C(m+(c-j)/2-1,m-1))%mod;
		//	cout<<i<<" "<<j<<" "<<cur<<endl;
			ans=(ans+cur)%mod;
		}
	}
	cout<<ans;
}
