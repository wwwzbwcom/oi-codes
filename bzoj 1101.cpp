#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=50000;
int gn,a,b,c,mni;
int boo[100100];
int pri[100100],pn=0;
int mob[100100];
long long ans=0;
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
int main()
{
	init();
	scanf("%d",&gn);
	while(gn--)
	{
		ans=0;
		scanf("%d%d%d",&a,&b,&c);
		a/=c;
		b/=c;
		mni=min(a,b);
		for(int i=1;i<=mni;)
		{
			int up=min(a/(a/i),b/(b/i));
			up=min(up,mni);
			ans+=(long long)(mob[up]-mob[i-1])*(long long)(a/i)*(long long)(b/i);
			i=up+1;
		}
		printf("%lld\n",ans);
	}
}
