#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
struct Output
{
	int u,v;
	bool operator<(const Output a)const
	{
		if(a.u==u) return a.v>v;
		return a.u>u;
	}
}a[20100];
int map[200][200];
int vis[200],low[200];
int cnt=0,ac=0;
int n,m,u,v;
char t;
int dfs(int u,int fa)
{
	low[u]=vis[u]=++cnt;
	int child=0;
	for(int i=0;i<n;i++)
	{
		int v=i;
		if(map[u][v]==0) continue;
		if(vis[v]==0)
		{
			child++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>vis[u])
			{
				//cout<<u<<"="<<v<<endl;
				a[ac].u=min(u,v);
				a[ac].v=max(u,v);
				ac++;
			}
		}
		else if(v!=fa) low[u]=min(low[u],vis[v]);
	}
//	if(fa==-1&&child==1) ac--,ans--;
}
void init()
{
	memset(map,0,sizeof map);
	memset(vis,0,sizeof vis);
	memset(low,0,sizeof low);
	cnt=0,ac=0;
}
int main()
{
	while(cin>>n)
	{
		init();
		for(int i=0;i<n;i++)
		{
			cin>>u;
			cin>>t>>m>>t;
			for(int j=0;j<m;j++)
			{
				cin>>v;
				map[u][v]=1;
				map[v][u]=1;
			}
		}
		for(int i=0;i<n;i++)
			if(vis[i]==0)
				dfs(i,-1);
		sort(a,a+ac);
		cout<<ac<<" critical links"<<endl;
		for(int i=0;i<ac;i++)
			cout<<a[i].u<<" - "<<a[i].v<<endl;
		cout<<endl;
	}
 } 
