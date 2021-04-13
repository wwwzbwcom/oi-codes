#include<algorithm>
#include<cstdio>
//#include<iostream> 
using namespace std;
int n,m,len; 
int sto[1600][1600];
int tmp[1600][1600];
int sum[1600][1600];
int dyp[1600][1600][5];
void init()
{
	scanf("%d%d%d",&n,&m,&len);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&sto[i][j]);
	
	for(int j=1;j<=m;j++)
	{
		int ans=0;
		for(int i=1;i<len;i++)	ans+=sto[i][j];
		for(int i=1;i<=n-len+1;i++)	ans-=sto[i-1][j],ans+=sto[i+len-1][j],tmp[i][j]=ans;//,cout<<sto[i-1][k]<<" "<<sto[i+k-1][j]<<endl;
	}
	for(int i=1;i<=n-len+1;i++)
	{
		int ans=0;
		for(int j=1;j<len;j++)	ans+=tmp[i][j];
		for(int j=1;j<=m-len+1;j++)	ans-=tmp[i][j-1],ans+=tmp[i][j+len-1],sum[i][j]=ans; 
	}
	/*
	cout<<"======================="<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cout<<sum[i][j]<<" ";
		cout<<endl;
	}
	*/
}
int work()
{
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m+1;j++)
			for(int k=1;k<=3;k++)
			{
				if(i-len>=1)	dyp[i][j][k]=max(dyp[i][j][k],dyp[i-len][m+1][k]);
				dyp[i][j][k]=max(dyp[i][j][k],max(dyp[i-1][j][k],dyp[i][j-1][k]));
				
				if(j-len>=1)	dyp[i][j][k]=max(dyp[i][j][k],dyp[i][j-len][k-1]+sum[i][j-len]);
			}
	return dyp[n+1][m+1][3];
}
int main()
{	
	init();
	printf("%d",work());
}
