#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
int gn,n;
int sto[maxn];
int dyp[maxn][5];
int main()
{
	scanf("%d",&gn); 
	for(int g=1;g<=gn;g++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
		dyp[0][0]=0;
		dyp[0][1]=-1e9;
		dyp[0][2]=-1e9;
		dyp[0][3]=-1e9;
		dyp[0][4]=-1e9; 
		for(int i=1;i<=n;i++)
		{
			dyp[i][0]=0;
			dyp[i][1]=max(dyp[i-1][1],dyp[i][0]-sto[i]);
			dyp[i][2]=max(dyp[i-1][2],dyp[i][1]+sto[i]);
			dyp[i][3]=max(dyp[i-1][3],dyp[i][2]-sto[i]);
			dyp[i][4]=max(dyp[i-1][4],dyp[i][3]+sto[i]);
		}
		
		printf("%d\n",dyp[n][4]);
	}
	
}
