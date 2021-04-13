#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
double x[1000],y[1000];
struct Edge
{
	int u,v;
	double c;
	bool operator<(const Edge in)const
	{
		return c<in.c;
	}
}e[1000000];
int fa[1000];
int s,p;
int en=0;
int cnt=0;
double ans=0;
int find(int u)
{
	if(fa[u]==-1)	return u;
	return fa[u]=find(fa[u]);
}
int main()
{
	memset(fa,-1,sizeof fa);
	cin>>s>>p;
	for(int i=1;i<=p;i++)	cin>>x[i]>>y[i];
	for(int i=1;i<=p;i++)
		for(int j=i+1;j<=p;j++)
			e[en].u=i,e[en].v=j,e[en].c=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])),en++;
	sort(e,e+en);
	for(int i=0;i<en;i++)
	{
		int u=e[i].u,v=e[i].v;
		double c=e[i].c;
		if(find(u)!=find(v))
		{
			fa[find(u)]=find(v);
			cnt++;
			ans=c;
		}
		if(cnt==p-s)	break;
	}
	printf("%.2lf",ans);
}
