#include<iostream>
using namespace std;
int n;
int edg[20][20];
int dyp[100100][20];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>edg[i][j];
	for(int i=0;i<100100;i++)	for(int j=0;j<20;j++)	dyp[i][j]=1e9;
	dyp[1][1]=0;
	for(int k=0;k<=(1<<n)-1;k++)
	{
		for(int i=1;i<=n;i++)	if((k&(1<<(i-1)))&&dyp[k][i]!=1e9)
			for(int j=1;j<=n;j++)	if((k&(1<<(j-1)))==0&&i!=j)
				dyp[(k|(1<<(j-1)))][j]=min(dyp[(k|(1<<(j-1)))][j],dyp[k][i]+edg[i][j]);
	}
	cout<<dyp[(1<<n)-1][n];
}
