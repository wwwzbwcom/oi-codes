#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=1100;
int n,kn;
int x[maxn],y[maxn],k[maxn];
double getdis(int i,int j)
{
	return sqrt((long long)(x[i]-x[j])*(x[i]-x[j])+(long long)(y[i]-y[j])*(y[i]-y[j]));
}
class Tree
{
	private:
		class Edge
		{
			public:
				int v,nxt;
				double c;
		}e[maxn*2];
		int pre[maxn],en;
		void dfsdyp(int u,int f)
		{
			double tmp[30];
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;	double c=e[i].c;
				if(v!=f)
				{
					dfsdyp(v,u);
					for(int k=0;k<2;k++)
					{
						for(int i=0;i<kn;i++)	tmp[i]=dyp[u][i][k];
						for(int p=kn-1;p>=0;p--)	if(dyp[u][p][k]<1e100)
						{
							for(int q=0;q<kn;q++)	if(dyp[v][q][0]<1e100)
								tmp[(p+q)%kn]=min(tmp[(p+q)%kn],max(max(dyp[u][p][k],dyp[v][q][0]),c));
							for(int q=0;q<kn;q++)	if(dyp[v][q][1]<1e100)
								tmp[(p+q)%kn]=min(tmp[(p+q)%kn],max(max(dyp[u][p][k],dyp[v][q][1]),c));
						}
						for(int i=0;i<kn;i++)	dyp[u][i][k]=tmp[i];
					}
				}
			}
			
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		double dyp[maxn][30][2];
		double ans;
		void addedge(int u,int v,double c)
		{
			
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{
			ans=1e100;
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)	for(int k=0;k<kn;k++)	dyp[j][k][0]=dyp[j][k][1]=1e100;
				for(int j=0;j<n;j++)	dyp[i][k[i]%kn][1]=dyp[i][0][0]=0;
				dfsdyp(i,-1);
				for(int i=0;i<n;i++)	ans=min(ans,dyp[i][0][1]); 
			}
		}
}tr;
class SCS
{ 
	public: 
		class Edge
		{
			public:
				int u,v;
				double c;
				bool operator <(const Edge &in)const
				{
					return c<in.c;
				}
		}e[maxn*maxn];
		int en;
		int fat[maxn];
		void build()
		{
			sort(e,e+en);
			for(int i=0;i<n;i++)	fat[i]=i;
			for(int i=0;i<en;i++)
			{
				int u=e[i].u,v=e[i].v;	double c=e[i].c;
				if(find(u)!=find(v))
				{
					fat[find(u)]=find(v);
					tr.addedge(u,v,c);
				}
			}
		}
		int find(int u)
		{
			if(fat[u]==u)	return u;
			return fat[u]=find(fat[u]);
		}
}sc;
int main()
{
	freopen("build.in","r",stdin);
	freopen("build.out","w",stdout);
	scanf("%d%d",&n,&kn);
	for(int i=0;i<n;i++)	scanf("%d%d%d",&x[i],&y[i],&k[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			sc.e[sc.en].u=i,sc.e[sc.en].v=j,sc.e[sc.en].c=getdis(i,j),sc.en++;
	sc.build();
	tr.build();
	printf("%.3lf\n",tr.ans);
}
