#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector <int> ev[200];
int dis[200];
bool vis[200];
int n,a,b;
int SPFA()
{
	queue <int> q;
	for(int i=0;i<200;i++)	dis[i]=2e9;
	dis[a]=0;
	vis[a]=1;
	q.push(a);
	
	while(!q.empty())
	{
		int u=q.front();	q.pop();	vis[u]=0;
		int len=ev[u].size();
		for(int i=0;i<len;i++)
		{
			int v=ev[u][i],c;
			if(i==0)	c=0;	else	c=1;
			if(dis[v]>dis[u]+c)
			{
				dis[v]=dis[u]+c;
				if(vis[v]==0)
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
	return dis[b];
}
int main()
{
	cin>>n>>a>>b;
	for(int	u=1;u<=n;u++)
	{
		int m;	cin>>m;
		for(int i=1;i<=m;i++)
		{
			int v;	cin>>v;
			ev[u].push_back(v);
		}
	}
	cout<<SPFA()<<endl;
}
