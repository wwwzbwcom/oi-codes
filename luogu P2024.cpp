#include<iostream>
using namespace std;
int n,m;
int fa[100000];
int dis[100000];
int find(int u)
{
	if(fa[u]==0)
	{
		dis[u]=0;
		return u;
	}
	int uf=find(fa[u]);
	dis[u]=dis[u]+dis[fa[u]];
	fa[u]=uf;
	return uf;
}
int main()
{
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int cd,u,v;
		cin>>cd>>u>>v;
		if(u<1||v<1||u>n||v>n)	ans++;
		else
		{
			int uf=find(u),vf=find(v);
			if(cd==1)
			{
				if(uf==vf)	{if((dis[u]-dis[v]+6)%3!=0)	ans++;}
				else	fa[uf]=vf,dis[uf]=(dis[v]-dis[u]+6)%3;
			}
			else
			{
				if(uf==vf)	{if((dis[u]-dis[v]+6)%3!=1)	ans++;}
				else	fa[uf]=vf,dis[uf]=(dis[v]-dis[u]+6+1)%3;
			}
		}
	}
	cout<<ans<<endl;
}
