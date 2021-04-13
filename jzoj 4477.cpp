#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
long long gn;
long long n,m,k,p;
long long ans;
long long bin[100],bim[100];
int main()
{
//	freopen("table.in","r",stdin);
//	freopen("table.out","w",stdout);
	cin>>gn;
	for(long long g=1;g<=gn;g++)
	{
		cin>>n>>m>>k>>p;
		ans=0;
		memset(bin,0,sizeof bin);
		memset(bim,0,sizeof bim);
		if(n<=100&&m<=100&&k<=100)
		{
			for(long long i=0;i<n;i++)
				for(long long j=0;j<m;j++)
					ans=(ans+max(0ll,(i^j)-k))%p;
			cout<<ans<<endl;
		}
		else
		{
			long long cnt;
			cnt=0;	while((1ll<<cnt)<n)	cnt++;
			cnt--;
			
			for(long long i=n-1;i>0;)
			{
				long long end=(1ll<<cnt);
			//	cout<<end<<" "<<i<<endl;
				bin[cnt]=i-end+1;
				i=end-1;
				cnt--;
			}
			cnt=0;	while((1ll<<cnt)<m)	cnt++;
			cnt--;
			//cout<<cnt<<endl;
			for(long long i=m-1;i>0;)
			{
				long long end=(1ll<<cnt);
				bim[cnt]=i-end+1;
				i=end-1;
				cnt--;
			}
			for(long long i=0;i<100;i++)	bin[i]%=p,bim[i]%=p;
			for(long long i=0;i<100;i++)
			{
				long long tmp=0;
				tmp+=(bin[i]*(m-bim[i])%p)%p;	tmp%=p;
				tmp+=(bim[i]*(n-bin[i])%p)%p;	tmp%=p;
				ans+=(tmp*(1ll<<i)%p)%p;
			//	if(i<=10)
			//	cout<<i<<" "<<bin[i]<<" "<<bim[i]<<" "<<ans<<endl;
			}
			if(k==0)	cout<<(ans%p+p)%p<<endl;
			else	cout<<((ans-(n%p*m%p)%p+min(n,m)%p)%p+p)%p<<endl;
		}
	}
}
