#include<algorithm>
#include<cstdio>
#include<iostream> 
using namespace std;
int n,m,len; 
int sto[1600][1600];
int tmp[1600][1600];
int sum[1600][1600];
int fdp[1600][1600][5];
int gdp[1600][5];
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
	
	cout<<"======================="<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cout<<sum[i][j]<<" ";
		cout<<endl;
	}
	
}
int work()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=len;j<=m;j++)
			for(int k=1;k<=3;k++)
				fdp[i][j][k]=max(fdp[i][j][k],fdp[i][j-1][k]),
				fdp[i][j][k]=max(fdp[i][j][k],fdp[i][j-len][k-1]+sum[i][j-len+1]);
	}
	for(int i=1;i<=n;i++)	cout<<fdp[i][m][2]<<endl;
	for(int i=len;i<=n;i++)
	{
		for(int p=0;p<=3;p++)
			for(int q=0;q<=3;q++)	if(p+q<=3)
				gdp[i][p+q]=max(gdp[i][p+q],gdp[i-1][p+q]),
				gdp[i][p+q]=max(gdp[i][p+q],gdp[i-len][p]+fdp[i-len+1][m][q]);
	}
	return gdp[n][3];
}
int main()
{	
	init();
	printf("%d",work());
}
