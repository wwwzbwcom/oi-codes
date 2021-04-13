#include<algorithm>
#include<cstdio>
using namespace std;
int gn,n;
int sto[100100];
int dyp[100100][2];
int main()
{
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
		for(int i=1;i<=n;i++)
		{
			dyp[i][0]=max(dyp[i-1][0],dyp[i-1][1]);
			dyp[i][1]=dyp[i-1][0]+sto[i];
		}
		printf("%d\n",max(dyp[n][0],dyp[n][1]));
	}
}
