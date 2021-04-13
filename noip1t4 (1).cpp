#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=999999999;
struct Edge
{
	int v,c;
	int next;
}e[201000];
int pre[2000];
int vis[2000];
int dis[20][2000];
int start[20];
int end[20];
int used[20];
int en=0;
int n,m,p,q;
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].next=pre[v];pre[v]=en++;
}
int SPFA(int num)
{
	memset(vis,0,sizeof vis);
	queue<int>q;
	for(int i=0;i<=2000;i++) dis[num][i]=oo;
	q.push(start[num]);
	dis[num][start[num]]=0;
	vis[start[num]]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v,c=e[i].c;
			if(dis[num][u]+c<dis[num][v])
			{
				dis[num][v]=dis[num][u]+c;
				if(vis[v]==0)
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}
int dfs(int num,int times)
{
	if(num==p+1)
	{
		for(int i=1;i<=q;i++)
		{
		//	cout<<used[i]<<" ";
			if(used[i]==0)
			{
		//		cout<<endl;
				return oo;
			} 
		}
	//	cout<<endl;
		return times;
	}
	int ans=oo;
	ans=min(ans,dfs(num+1,times));
	for(int i=1;i<=q;i++)
	{
		if(used[i]==0)
		{
			used[i]=1;
	//		cout<<num<<" "<<i<<endl;
			ans=min(ans,dfs(num+1,max(times,dis[num][end[i]])));
			used[i]=0;
		}
	}
	return ans;
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		addedge(u,v,c);
	}
	cin>>p>>q;
	for(int i=1;i<=p;i++)
	{
		cin>>start[i],SPFA(i);
	//	for(int j=1;j<=n;j++)
	//		cout<<dis[i][j]<<" ";
	//	cout<<endl;
	}
	
	for(int i=1;i<=q;i++) cin>>end[i];
	cout<<dfs(1,0);
}
