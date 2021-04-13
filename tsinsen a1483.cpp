#include<cstdio>
//#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200;
int n,t;
long long val[maxn][maxn];
long long dyp[maxn][maxn];
long long a[maxn],b[maxn];
int main()
{
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)	scanf("%lld",&b[i]); 
	for(int i=1;i<=n;i++)	for(int j=1;j<=n;j++)	val[i][j]=a[i]*b[j];
	for(int k=1;k<=t;k++)
	{
		int p,q,r,s;	scanf("%d%d%d%d",&p,&q,&r,&s);
		for(int i=0;i<maxn;i++)	for(int j=0;j<maxn;j++)	dyp[i][j]=1e18;
		dyp[p][q]=val[p][q];
		for(int i=p;i<=n;i++)
			for(int j=q;j<=n;j++)	if(i!=p||j!=q)
				dyp[i][j]=min(dyp[i-1][j],dyp[i][j-1])+val[i][j];
		printf("%lld\n",dyp[r][s]);
	}
}
