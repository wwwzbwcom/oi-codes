#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v,c;
	bool operator<(const Edge in)const
	{return c>in.c;}
}e[100100];
int n,m;
int fat[100100];
int dis[100100];
int find(int u)
{
	if(fat[u]==-1)
	{
		dis[u]=0;
		return u;
	}
	else
	{
		int uf=find(fat[u]);
		dis[u]=(dis[u]+dis[fat[u]]+2)%2;
		fat[u]=uf;
		return uf;
	}
}
int main()
{
	memset(fat,-1,sizeof fat);
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)	scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
	sort(e,e+m);
	int ans=0;
	for(int i=0;i<m;i++)
	{
		int u=e[i].u,v=e[i].v,c=e[i].c;
		int uf=find(u),vf=find(v);
		if(uf==vf)
		{
			if((dis[u]-dis[v]+2)%2==0){ans=c;break;}
		}
		else
		{
			if((dis[u]-dis[v]+2)%2==0)
			{
				dis[uf]=1;
				fat[uf]=vf;
			}
			else
			{
				dis[uf]=0;
				fat[uf]=vf;
			}
		}	
	}
	cout<<ans<<endl;
}
