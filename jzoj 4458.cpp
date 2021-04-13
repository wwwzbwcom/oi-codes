#include<iostream>
using namespace std;
const long long maxn=1e7+10;
long long boo[maxn];
long long pri[maxn],pn;
long long e,N,c;
long long p,q,r;
long long d,n;
void init()
{
	boo[1]=1;
	for(long long i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(long long j=1;j<=pn;j++)
		{
			if(i*pri[j]>maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
long long mul(long long a,long long b,long long mod)
{
	if(b==0)	return 0;
	else
	{
		long long ans=mul(a,b/2,mod);
	//	cout<<b/2<<" "<<ans<<endl; 
		ans=(ans+ans)%mod;
		if(b%2==0)	return ans;
		else	return (ans+a)%mod;
	}
}
long long qsm(long long a,long long b,long long mod)
{
	if(b==0)	return 1;
	else
	{
		long long ans=qsm(a,b/2,mod);
		ans=mul(ans,ans,mod);
		if(b%2==0)	return ans;
		else	return mul(ans,a,mod);
	}
}
int main()
{
//	int mod=97;
//	cout<<(qsm(15,mod-1,mod)*15)%mod;
	init();
	cin>>e>>N>>c;
	for(long long i=1;i<=pn;i++)
		if(N%pri[i]==0)
		{
			p=pri[i];
			q=N/pri[i];
			break;
		}
	r=(p-1)*(q-1);
	for(int i=0;i<r;i++)
		if((e*i)%r==1)
		{
			d=i;
			break;
		}
	n=qsm(c,d,N);
	cout<<d<<" "<<n<<endl; 
}
