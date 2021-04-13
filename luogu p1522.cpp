#include<iostream>
#include<cmath>
using namespace std;
int n;
double x[200],y[200];
double dis[200][200];
double far[200];
int blo[200],bn=0;
int r[200][2];
double getdis(int a,int b)
{
	return	sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			char t;cin>>t;
			if(t=='1')	dis[i][j]=getdis(i,j);
			else	dis[i][j]=1e10;
		}
	for(int i=1;i<=n;i++)	dis[i][i]=0;
	
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	
	for(int i=1;i<=n;i++)
		if(blo[i]==0)
		{
			bn++;
			double maxn=-1;	int p1,p2;
			for(int j=1;j<=n;j++)	if(dis[i][j]<1e9)	blo[j]=bn;
			for(int j=1;j<=n;j++)	if(dis[i][j]<1e9&&dis[i][j]>maxn)	maxn=dis[i][j],p1=j;
			maxn=-1;
			for(int j=1;j<=n;j++)	if(dis[p1][j]<1e9&&dis[p1][j]>maxn)	maxn=dis[p1][j],p2=j;
			if(p1>p2)	swap(p1,p2);
			r[bn][0]=p1;r[bn][1]=p2;
		//	cout<<"=========="<<endl;
		}
	double ans=1e10;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(blo[i]!=blo[j])
			{
				int pi0=r[blo[i]][0],pi1=r[blo[i]][1];
				int pj0=r[blo[j]][0],pj1=r[blo[j]][1];
				double	t=max( max(dis[pi0][pi1],dis[pj0][pj1]), max(dis[i][pi0],dis[i][pi1])+max(dis[j][pj0],dis[j][pj1])+getdis(i,j) );
				ans=min(ans,t);
			}
	
	printf("%.6lf",ans);
}
