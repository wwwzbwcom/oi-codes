#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1000000;
const int oo=1e9;
int n,m;
int sum;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
	}
	struct Edge
	{
		int v;
		double c;
		int nxt;
	}e[maxn];
	int pre[maxn],en;
	int lev[maxn];
	int sta,end;
	void addedge(int u,int v,double c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	bool bfs()
	{
		queue <int> que;	memset(lev,-1,sizeof lev);
		que.push(sta);	lev[sta]=1;
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;	double c=e[i].c;
				if(lev[v]==-1&&c>1e-10)
				{
					lev[v]=lev[u]+1;
					if(v==end)	return 1;
					que.push(v); 
				}
			}
		}
		return 0;
	}
	double dfs(int u,double lc)
	{
		if(u==end)	return lc;
		double nc=0;
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
		{
			int v=e[i].v;	double c=e[i].c;
			if(lev[v]==lev[u]+1&&c>1e-10)
			{
				double cc=min(c,lc-nc);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc==0)	lev[u]=-1;
		return nc;	
	}
	double dinic()
	{
		double ans=0;
		while(bfs())	ans+=dfs(sta,oo);
		return ans;
	}
}d;
int main()
{
	cin>>n>>m;
	d.sta=n*m;	d.end=n*m+1;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			int val;	cin>>val;	sum+=val;
			d.addedge(d.sta,i*m+j,val);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			int val;	cin>>val;	sum+=val;
			d.addedge(i*m+j,d.end,val);
		}
	for(int i=0;i<n-1;i++)
		for(int j=0;j<m;j++)
		{
			double val;	cin>>val;	sum+=val;
			d.addedge(i*m+j,(i+1)*m+j,val/2),d.addedge((i+1)*m+j,i*m+j,val/2);
			d.addedge(d.sta,i*m+j,val/2),d.addedge(d.sta,(i+1)*m+j,val/2);
		}
	for(int i=0;i<n-1;i++)
		for(int j=0;j<m;j++)
		{
			double val;	cin>>val;	sum+=val;
			d.addedge(i*m+j,(i+1)*m+j,val/2),d.addedge((i+1)*m+j,i*m+j,val/2);
			d.addedge(i*m+j,d.end,val/2),d.addedge((i+1)*m+j,d.end,val/2);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m-1;j++)
		{
			double val;	cin>>val;	sum+=val;
			d.addedge(i*m+j,i*m+j+1,val/2),d.addedge(i*m+j+1,i*m+j,val/2);
			d.addedge(d.sta,i*m+j,val/2),d.addedge(d.sta,i*m+j+1,val/2);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m-1;j++)
		{
			double val;	cin>>val;	sum+=val;
			d.addedge(i*m+j,i*m+j+1,val/2),d.addedge(i*m+j+1,i*m+j,val/2);
			d.addedge(i*m+j,d.end,val/2),d.addedge(i*m+j+1,d.end,val/2);
		}
	cout<<sum-(int)d.dinic();
}
