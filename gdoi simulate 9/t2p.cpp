#include<iostream>
#include<cstring>
using namespace std;
const int maxn=10000;
struct Graph
{
	Graph()
	{
		memset(pre,-1,sizeof pre);en=0;
	}
	struct Edge
	{
		int v,c,nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int vis[maxn];
	void addedge(int u,int v,int c)
	{
		e[en].v=v;	e[en].c=c;	e[en].nxt=pre[u];	pre[u]=en++;
		e[en].v=u;	e[en].c=c;	e[en].nxt=pre[v];	pre[v]=en++;
	}
	void dfs(int u,int lim)
	{
		vis[u]=1;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(!vis[v]&&c<=lim)	dfs(v,lim);
		}
	}
	int work(int u,int v,int lim)
	{
		memset(vis,0,sizeof vis);
		dfs(u,lim);
		return vis[v];
	}
}g;
int n,m,c;
int tim,lie;
int main()
{
//	freopen("data2.txt","r",stdin);
//	freopen("data2.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		char cmd[10];	int x,y,t;	cin>>cmd;
		if(cmd[0]=='K')	cin>>x,c=x,lie=0;
		if(cmd[0]=='R')
		{
			tim++;	cin>>x>>y;
			if(lie)	x=((x+c)%n+n)%n,y=((y+c)%n+n)%n;
			g.addedge(x,y,tim);
		}
		if(cmd[0]=='T')
		{
			cin>>x>>y>>t;
			if(g.work(x,y,tim)&&!g.work(x,y,tim-t))	lie=0,cout<<'Y'<<endl;
			else	lie=1,cout<<"N"<<endl;
		}
	}
}
