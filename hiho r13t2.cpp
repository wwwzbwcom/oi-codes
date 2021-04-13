#include<cstdio>
int n,m;
double dyp[200][1000];
int main()
{
	scanf("%d%d",&n,&m);
	dyp[0][0]=100;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=6&&j-k>=0;k++)
				dyp[i][j]+=dyp[i-1][j-k]*(1.0/6.0);
	printf("%.2lf",dyp[n][m]);
}
