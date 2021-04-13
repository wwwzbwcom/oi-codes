#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=500100;
int boo[maxn];
int pri[maxn],pn;
int mob[maxn];
void init()
{
	boo[1]=1;	mob[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i,mob[i]=-1;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				mob[i*pri[j]]=0;
				break;
			}
			else	mob[i*pri[j]]=-mob[i];
		}
	}
	for(int i=1;i<maxn;i++)	mob[i]+=mob[i-1];
}
int work(int a,int b)
{
	if(a==0||b==0)	return 0;
	int lim=min(a,b),ans=0,end=0;
//	for(int i=1;i<=lim;i++)	ans+=(a/i)*(b/i)*mob[i];
//	return ans;
	for(int i=1;i<=lim;i=end+1)
	{
		end=min(lim,min(a/(a/i),b/(b/i)));
		ans+=(a/i)*(b/i)*(mob[end]-mob[i-1]);
	}
	return ans;
}
int main()
{
	int gn;	scanf("%d",&gn);
	init();
//	for(int i=1;i<=10;i++)	cout<<i<<" "<<mob[i]<<endl;
	for(int g=1;g<=gn;g++)
	{
		int a,b,c,d,k;	scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%d\n",work(b/k,d/k)-work((a-1)/k,d/k)-work(b/k,(c-1)/k)+work((a-1)/k,(c-1)/k));
	}
}
