#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=600;
int n,m;
int x[maxn],y[maxn];
int dyp[maxn][maxn];
int getdis(int i,int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d%d",&x[i],&y[i]);
	for(int i=0;i<maxn;i++)	for(int j=0;j<maxn;j++)	dyp[i][j]=2e9; 
	dyp[1][0]=0;
	for(int i=1;i<=n;i++)
		for(int k=0;k<=min(m,i-2);k++)
			for(int j=i-k-1;j<=i-1;j++)
				dyp[i][k]=min(dyp[i][k],dyp[j][k-(i-j-1)]+getdis(i,j));
	printf("%d",dyp[n][m]);
}
