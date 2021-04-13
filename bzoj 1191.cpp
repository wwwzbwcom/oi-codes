#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v;
	int nxt;
}e[20100];
int n,m;
int pre[2100],en=0;
int mat[2100];
int vis[2100];
int ans=0;
void addedge(int u,int v)
{
	e[en].u=u;e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].u=v;e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
int dfs(int u)
{
	vis[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]==-1)
		{
			vis[v]=1;
			if(mat[v]==-1||dfs(mat[v]))
			{
				mat[v]=u;
				return 1;
			} 
		}
	}
	return 0;
}
int main()
{
	memset(pre,-1,sizeof pre);
	memset(mat,-1,sizeof mat);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;	cin>>a>>b;
		addedge(i,m+a);
		addedge(i,m+b);
	}
	for(int i=0;i<m;i++)
	{
		memset(vis,-1,sizeof vis);
		if(dfs(i))	ans++;	else	break;
	}
	cout<<ans<<endl;
}
