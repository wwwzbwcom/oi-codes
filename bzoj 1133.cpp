#include<iostream>
using namespace std;
int n,kn;
int peo[1000][1000];
int aft[1000][1000];	//start from i, end after j(include j)
int sum[1000][1000];
int dyp[1000][100];
int main()
{
	cin>>n>>kn;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			cin>>peo[i][j];
	for(int i=1;i<=n;i++)
		for(int j=n;j>=i+1;j--)
			aft[i][j]=aft[i][j+1]+peo[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
			sum[i][j]=sum[i-1][j]+peo[i][j];
	}
	for(int i=1;i<=n;i++)
	{
		for(int k=1;k<=kn;k++)
		{
			dyp[i][k]=dyp[i-1][k];
			for(int j=0;j<i;j++)	dyp[i][k]=max(dyp[i][k],dyp[j][k-1]+sum[j+1][i]);
		}
	}
	cout<<dyp[n][kn]<<endl;
}
