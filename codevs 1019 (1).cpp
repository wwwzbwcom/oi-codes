#include<iostream>
#include<cstring>
using namespace std;
int map[1010][1010];
int s[1010];
int vis[1010];
int se=0;
int gn;
int n,m;
int flag=0;
bool dfs(int u)
{
	vis[u]=1;
	for(int f=0;f<se;f++)
		if(map[s[f]][u]==0) return 0;
	s[se++]=u;
	for(int v=1;v<=n;v++)
		if(map[u][v]==1)
			if(dfs(v)==0)
			{
				se--;
				return 0;	
			}
	se--;
	return 1;
}
int main()
{
	cin>>gn;
	while(gn--)
	{
		memset(vis,0,sizeof vis);
		memset(map,0,sizeof map);
		flag=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			map[u][v]=1;
		}
		for(int i=1;i<=n;i++)
			if(vis[i]==0&&dfs(i)==0)
			{
				flag=1;
				break;
			}
		if(flag==1) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
}
