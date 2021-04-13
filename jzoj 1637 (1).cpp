#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=200;
const int oo=1e9;
int n,m;
int map[maxn][maxn];
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
	}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[maxn*maxn*10];
	int pre[maxn*maxn],en;
	int lev[maxn*maxn];
	int sta,end;
	void addedge(int u,int v,int c)
	{
	//	cout<<u<<"="<<v<<"="<<c<<endl;
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	int bfs()
	{
		queue <int> que;	memset(lev,-1,sizeof lev);
		que.push(sta);	lev[sta]=1;
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==-1&&c)
				{
					lev[v]=lev[u]+1;
					if(v==end)	return 1;
					que.push(v);
				}
			}
		}
		return 0;
	}
	int dfs(int u,int lc)
	{
		if(u==end)	return lc;
		int nc=0;
		for(int i=pre[u];i!=-1&&lc-nc>0;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			
			if(lev[v]==lev[u]+1&&c)
			{
				int cc=min(c,lc-nc);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc==0)	lev[u]=2;
		return nc;
	}
	int dinic()
	{
		int ans=0;
		while(bfs())	ans+=dfs(sta,oo);//,cout<<ans<<endl,getchar();
		return ans;
	}
}din;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>map[i][j];
			if(map[i][j]==0)	map[i][j]+=3;
		}
	din.sta=n*m+1;
	din.end=n*m+2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			for(int p=-1;p<=1;p++)
				for(int q=-1;q<=1;q++)	if(abs(p)+abs(q)==1&&map[i+p][j+q]!=0)
				{
					if(map[i][j]==map[i+p][j+q])	din.addedge((i-1)*m+j,(i+p-1)*m+(j+q),1);
					else	din.addedge((i-1)*m+j,(i+p-1)*m+(j+q),1);
					
					if(map[i][j]==1)	din.addedge(din.sta,(i-1)*m+j,oo);
					if(map[i][j]==2)	din.addedge((i-1)*m+j,din.end,oo);
				}
		}
	cout<<din.dinic()<<endl;
}
