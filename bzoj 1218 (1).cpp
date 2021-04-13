#include<iostream> 
#include<cstdio>
using namespace std;
int n,r;
short sto[5100][5100];
short sum[5100][5100];
int cur=0;
int ans=0;
int main()
{
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)
	{
		int x,y,v;scanf("%d%d%d",&x,&y,&v);
		sto[x][y]=v;
	}
	for(int j=0;j<=5000;j++)
		for(int i=0;i<r;i++)
			sum[0][j]+=sto[i][j];
	for(int i=1;i<=5000-r+1;i++)
		for(int j=0;j<=5000;j++)
			sum[i][j]=sum[i-1][j]-sto[i-1][j]+sto[i+r-1][j];
	for(int i=0;i<=5000-r+1;i++)
	{
		cur=0;
		for(int j=0;j<r;j++)	cur+=sum[i][j];
		ans=max(ans,cur);
		for(int j=r;j<=5000;j++)
		{
			cur-=sum[i][j-r];
			cur+=sum[i][j];
			ans=max(ans,cur);
		}
	}
	printf("%d\n",ans);
}
