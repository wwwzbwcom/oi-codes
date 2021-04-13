#include<cstdio>
using namespace std;
const int maxn=100;
int n,m;
char str[maxn][maxn];
long long dyp[maxn][maxn];
long long gcd(long long a,long long b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			scanf("%s",str[i]+j);

	dyp[0][0]=(1ll<<n);
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
		{
			if(str[i][j]=='*')	dyp[i+1][j]+=dyp[i][j]/2,dyp[i+1][j+1]+=dyp[i][j]/2;
			else				dyp[i+2][j+1]+=dyp[i][j];
		}
	
	if(dyp[n][m]==0)	printf("0/1\n");
	else
	{
		long long g=gcd(dyp[n][m],(1ll<<n));
		printf("%d/%d\n",dyp[n][m]/g,(1ll<<n)/g);
	}
}
