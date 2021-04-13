#include<stdio.h>
int n;
bool boo[1100];
int pri[1100],pn=0;
long long dyp[1100][1100];
long long ans=0;
void init()
{
	boo[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>n)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break; 
		}
	}
}
int main()
{
	scanf("%d",&n);
	init();
	dyp[0][0]=1;
	for(int i=0;i<pn;i++)
		for(int j=0;j<=n;j++)
		{
			dyp[i+1][j]+=dyp[i][j];
			int cur=pri[i+1];
			while(cur+j<=n)
			{
				dyp[i+1][j+cur]+=dyp[i][j];
				cur*=pri[i+1];
			}
		}
	for(int i=0;i<=n;i++)	ans+=dyp[pn][i];
	printf("%lld\n",ans);
}
