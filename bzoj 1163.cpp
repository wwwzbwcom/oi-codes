#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=1e9;
struct Edge
{
	int v,c;
	int nxt;
}e[320100];
int n,m,a,b;
int pre[500],en=0;
int lev[500];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
}
bool bfs()
{
	memset(lev,-1,sizeof lev);
	queue <int> que;
	que.push(a);lev[a]=0;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(lev[v]==-1&&c>0)
			{
				lev[v]=lev[u]+1;
				que.push(v);
			}
		}
	}
	if(lev[b]==-1)	return 0;
	else	return 1; 
}
int dfs(int u,int lc)
{
	if(u==b)	return lc;
	int nc=0;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(lev[v]==lev[u]+1&&c>0)
		{
			int cc=min(c,lc-nc);
			cc=dfs(v,cc);
			e[i].c-=cc;
			e[i^1].c+=cc;
			nc+=cc;
		}
	}
	if(nc==0)	lev[u]=-1;
	return nc;
}
int dinic()
{
	int ans=0,t;
	while(bfs())
	{
		t=dfs(a,oo);
		if(t)	ans+=t;
		else	break;
	}
	return ans;
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>m;
	cin>>a>>b;
	a=a*2-1;
	b=b*2;
	for(int i=1;i<=n;i++)
	{
		int c;cin>>c;
		addedge(i*2-1,i*2,c);
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		addedge(u*2,v*2-1,oo);
		addedge(v*2,u*2-1,oo);
	}
	cout<<dinic()<<endl; 
}
