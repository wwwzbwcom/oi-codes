#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=50000;
int gn;
int a,b,c,d,k;
int boo[100100];
int pri[100100],pn=0;
int mob[100100];
void init()
{
	boo[1]=1;mob[1]=1;
	for(int i=2;i<=maxn;i++)
	{
		if(boo[i]==0)	pri[pn++]=i,mob[i]=-1;
		for(int j=0;j<pn;j++)
		{
			if(i*pri[j]>maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				mob[i*pri[j]]=0;
				break; 
			} 
			else mob[i*pri[j]]=-mob[i];
		}
	}
	for(int i=1;i<=maxn;i++)	mob[i]+=mob[i-1];
}
long long work(long long a,long long b)
{
	long long ans=0;
	int upp=min(a,b);
	for(int i=1;i<=upp;)
	{
		int las=min((a/(a/i)),(b/(b/i)));
		las=min(las,upp);
		ans+=(mob[las]-mob[i-1])*(a/i)*(b/i);
		i=las+1;
	}
	return ans;
}
int main()
{
	init();
	scanf("%d",&gn);
	while(gn--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if(a%k==0)	a/=k;	else a=a/k+1;
		if(c%k==0)	c/=k;	else c=c/k+1;
		a--; c--;
		b/=k;d/=k;
		printf("%lld\n",work(b,d)-work(a,d)-work(b,c)+work(a,c));
	}
}
