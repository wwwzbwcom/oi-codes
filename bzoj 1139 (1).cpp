#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct Edge
{
	int v,c;
	int val;
	int nxt;
}e[10000];
int pre[500],en=0;
int n,m,p,k;
int poi[500];
int dis[500][20000];
int ans=-1;
void addedge(int u,int v,int c,int val)
{
	e[en].v=v;e[en].c=c;e[en].val=val;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].val=val;e[en].nxt=pre[v];pre[v]=en++;
}
struct n4d
{
	n4d(int ui,int coni,int di){u=ui;con=coni;d=di;}
	int u,con,d;
	bool operator<(const n4d &in)const
	{
		return d>in.d;
	}
};
void dijstra()
{
	memset(dis,-1,sizeof dis);	priority_queue <n4d> que;
	que.push(n4d(1,poi[1],0));
	
	while(!que.empty())
	{
		n4d cur=que.top();que.pop();
		int u=cur.u,con=cur.con,d=cur.d;
		if(dis[u][con]==-1)
		{
			dis[u][con]=d;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,val=e[i].val;
				if((con&val)==val)	que.push(n4d(v,(con|poi[v]),d+c));
			}
		}
	}
	
}
int main()
{
	memset(pre,-1,sizeof pre);
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for(int i=1;i<=k;i++)
	{
		int w,q;	scanf("%d%d",&w,&q);
		for(int j=1;j<=q;j++)
		{
			int t;	scanf("%d",&t);
			poi[w]=(poi[w]|(1<<(t-1)));
		}
	}
	
	for(int i=1;i<=m;i++)
	{
		int x,y,c,s;	scanf("%d%d%d%d",&x,&y,&c,&s);
		int v=0;
		for(int j=1;j<=s;j++)
		{
			int t;	scanf("%d",&t);
			v=(v|(1<<(t-1)));
		}
		addedge(x,y,c,v);
	}
	dijstra();
	for(int i=0;i<(1<<p);i++)
		if(dis[n][i]!=-1)
		{
			if(ans==-1)	ans=dis[n][i];
			else 	ans=min(ans,dis[n][i]);
		}
	printf("%d\n",ans);
}
