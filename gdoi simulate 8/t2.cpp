#include<algorithm> 
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=1000000;
int boo[maxn];
int pri[maxn],pn;
int mob[maxn];
int eul[maxn];
int cnt[maxn];
int sum,ans;
void mobius()
{
	boo[1]=1;	mob[1]=1;	eul[1]=0;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[pn++]=i,mob[i]=-1,eul[i]=1;
		for(int j=0;j<pn;j++)
		{
			if(pri[j]*i>=maxn)	break;
			boo[pri[j]*i]=1;
			eul[pri[j]*i]=eul[i]+1;
			if(i%pri[j]==0)
			{
				mob[pri[j]*i]=0;
				break;
			}
			else	mob[pri[j]*i]=-mob[i];
		}
	}
	for(int i=1;i<maxn;i++)	mob[i]+=mob[i-1];
}
int gn,n,m,p;
int main()
{
	mobius();
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%d%d%d",&n,&m,&p);
		memset(cnt,0,sizeof cnt);	ans=0;
		for(int i=1;i<=min(n,m);i++)	if(eul[i]<=p)	cnt[i]=1;
		for(int i=1;i<=min(n,m);i++)	cnt[i]+=cnt[i-1];
		int lii=min(n,m); 
		for(int i=1,eni;i<=lii;i=eni+1)
		{
			int a=n/i,b=m/i;
			eni=min(lii,min(n/(n/i),m/(m/i)));
			if(cnt[eni]-cnt[i-1]==0)	continue;
			sum=0;
			int lij=min(a,b);
			for(int j=1,enj;j<=lij;j=enj+1)
			{
				enj=min(lij,min(a/(a/j),b/(b/j)));
				sum+=(mob[enj]-mob[j-1])*(a/j)*(b/j);
			//	cout<<j<<"="<<enj<<" "<<mob[enj]<<" "<<mob[j-1]<<" "<<(a/j)*(b/j)<<endl;
			}
			//2cout<<i<<" "<<sum<<" "<<eni<<" "<<cnt[eni]<<endl;
			ans+=(cnt[eni]-cnt[i-1])*sum;
			//	cout<<i<<" "<<ans<<endl;
		}
		printf("%d\n",ans);
	}
}
