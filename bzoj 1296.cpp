#include<algorithm>
#include<cstdio>
using namespace std;
int n,m,t;
int sto[100][100];
int dyp[100][100][100];
int ans[100][100000];
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)
	{
		char t[100];
		scanf("%s",t);
		for(int j=1;j<=m;j++)
		{
			sto[i][j]=t[j-1]-'0';
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int p=1;p<=m;p++)	dyp[i][j][p]=max(dyp[i][j][p],dyp[i][j-1][p]),dyp[i][j][p]=max(dyp[i][j][p],dyp[i][j][p-1]);
			for(int k=1;k<=j;k++)
			{
				int cnt[2];	cnt[0]=cnt[1]=0;
				for(int p=k;p<=j;p++)	cnt[sto[i][p]]++;
				int mxa=max(cnt[0],cnt[1]);
			//	cout<<i<<" "<<j<<" "<<k<<endl;
				for(int p=1;p<=m;p++)	dyp[i][j][p]=max(dyp[i][j][p],dyp[i][k-1][p-1]+mxa);
			}
		}
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//			cout<<dyp[i][m][j]<<" ";
//		cout<<endl;
//	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=t;j++)
		{
			ans[i][j]=max(ans[i][j],ans[i-1][j]);
			if(j!=0)	ans[i][j]=max(ans[i][j],ans[i][j-1]);
			for(int k=0;k<=m;k++)
			{
				if(j-k>=0)	ans[i][j]=max(ans[i][j],ans[i-1][j-k]+dyp[i][m][k]);
			}
		}
	printf("%d\n",ans[n][t]);
}
