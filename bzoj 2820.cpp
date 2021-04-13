#include<algorithm> 
#include<cstdio>
using namespace std;
const int maxn=10000000;
long long gn,n,m;
long long boo[maxn+100];
long long pri[maxn+100],pn=0;
long long cnt[maxn+100];
long long sum[maxn+100];
long long ffu[maxn+100];
void init()
{
	boo[1]=1;
	cnt[1]=0;
	sum[1]=0;
	for(int i=2;i<=maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i,cnt[i]=1,sum[i]=1;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				cnt[i*pri[j]]=cnt[i];
				sum[i*pri[j]]=sum[i]+1;
				break;
			}
			else
			{
				cnt[i*pri[j]]=cnt[i]+1;
				sum[i*pri[j]]=sum[i]+1;
			}
		}
	}
	for(int i=1;i<=maxn;i++)
	{
		if(cnt[i]==sum[i])
		{
			if(cnt[i]%2==0)	ffu[i]=-cnt[i];
			else	ffu[i]=cnt[i];
		}
		else
		{
			if(cnt[i]==sum[i]-1)
			{
				if(cnt[i]%2==0)	ffu[i]=1;
				else	ffu[i]=-1;
			}
			else	ffu[i]=0;
		}
	}
	for(int i=1;i<=maxn;i++)	ffu[i]+=ffu[i-1];
}
int main()
{
	init();
//	for(int i=1;i<=10;i++)	cout<<cnt[i]<<" "<<sum[i]<<" "<<ffu[i]<<endl;
	scanf("%d",&gn);
	while(gn--)
	{
		scanf("%d%d",&n,&m);
		long long ans=0;
		for(int i=1;i<=min(n,m);)
		{
			long long end=min(n/(n/i),m/(m/i));
			end=min(min(n,m),end);
			ans+=(ffu[end]-ffu[i-1])*(n/i)*(m/i);
			i=end+1;
		}
		printf("%lld\n",ans);
	}
}
