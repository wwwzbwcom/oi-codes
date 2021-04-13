#include<cstdio>
using namespace std;
const int maxn=200;
int n,m;
int dis[maxn][maxn];
long long cnt[maxn][maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<maxn;i++)
		for(int j=0;j<maxn;j++)
			dis[i][j]=1e9;
	for(int i=0;i<maxn;i++)	dis[i][i]=0,cnt[i][i]=1;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		if(c<dis[u][v])	dis[u][v]=dis[v][u]=c,cnt[u][v]=cnt[v][u]=1;
		else	if(c==dis[u][v])	cnt[u][v]++,cnt[v][u]++;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)	if(i!=j&&i!=k&&j!=k)
			{
			//	if(i==1&&j==2)	cout<<i<<" "<<k<<" "<<j<<" "<<dis[i][k]<<"="<<dis[k][j]<<" "<<cnt[i][k]<<"="<<cnt[k][j]<<" "<<dis[i][j]<<"="<<cnt[i][j]<<endl;
				if(dis[i][j]>dis[i][k]+dis[k][j])
				{
					dis[i][j]=dis[i][k]+dis[k][j];
					cnt[i][j]=cnt[i][k]*cnt[k][j];
				}
				else	if(dis[i][j]==dis[i][k]+dis[k][j])	cnt[i][j]+=cnt[i][k]*cnt[k][j];
			//	if(i==1&&j==2)	cout<<i<<" "<<k<<" "<<j<<" "<<dis[i][k]<<"="<<dis[k][j]<<" "<<cnt[i][k]<<"="<<cnt[k][j]<<" "<<dis[i][j]<<"="<<cnt[i][j]<<endl;
			}
	for(int k=1;k<=n;k++)
	{
		double ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)	if(i!=k&&j!=k)
				if(dis[i][k]+dis[k][j]==dis[i][j])
				{
				//	cout<<k<<" "<<i<<" "<<j<<"=="<<endl;
					ans+=((double)cnt[i][k]/cnt[i][j])*cnt[k][j];
				}
		printf("%.3lf\n",ans);
	}
}
