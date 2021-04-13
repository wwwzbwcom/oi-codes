#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v;
	double c;
	bool operator<(const Edge a)const
	{
		return a.c<c;
	}
}e[100000];
int x[100000];
int y[100000];
int fa[100000];
int en,n,gn;
double ans=0;
double getdis(int i,int j)
{
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
void init()
{
	memset(fa,-1,sizeof fa);
	en=0;
	ans=0;
}
int find(int now)
{
	if(fa[now]==-1) return now;
	return fa[now]=find(fa[now]);
}
int main()
{
	scanf("%d",&gn);
	while(gn--)
	{
		init();
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d%d",&x[i],&y[i]);
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
			{
				double dis=getdis(i,j);
				if(10-1e-8<=dis&&dis<=1000+1e-8)
				{
					e[en].u=i;
					e[en].v=j;
					e[en].c=dis;
					en++;
				}
			}
		sort(e,e+en);
		for(int i=0;i<en;i++)
		{
			int u=e[i].u,v=e[i].v;
			if(find(u)!=find(v)) fa[find(u)]=find(v),ans+=e[i].c;
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(find(i)!=find(j))
					ans=-1;
		if(ans==-1) printf("oh!\n");
		else printf("%.1lf\n",ans*100);
	}
}
