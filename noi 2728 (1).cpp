#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int gn,r,c;
int num[110][110];
int main()
{
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%d%d",&r,&c);
		memset(num,0,sizeof num);
		for(int i=0;i<r;i++)
			for(int j=0;j<c;j++)
				scanf("%d",&num[i][j]);
		for(int i=r-1;i>=0;i--)
			for(int j=c-1;j>=0;j--)
				num[i][j]+=max(num[i+1][j],num[i][j+1]);
		printf("%d\n",num[0][0]);
	}
}
