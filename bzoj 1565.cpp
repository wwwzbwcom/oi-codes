#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<queue>
using namespace std;
const int maxn=1000;
const int oo=1e9;
int n,m;
int nn;
int sco[maxn];
int sum;
int dis[maxn][maxn];
class Tarjan
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn],low[maxn],vn;
		int ins[maxn];
		int bn;
		stack <int> sta;
		void dfs1(int u)
		{
			vis[u]=low[u]=++vn;	ins[u]=1;	sta.push(u);
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(vis[v]==0)	dfs1(v),low[u]=min(low[u],low[v]);
				else	if(ins[v])	low[u]=min(low[u],vis[v]);
			}
			if(vis[u]==low[u])
			{
				int t;	bn++;
				do
				{
					t=sta.top();	sta.pop();	ins[t]=0;
					bfa[t]=bn,	bsz[bn]++;
				}while(t!=u);
			}
		}
	public:
		int fob[maxn],bfa[maxn],bsz[maxn];
		Tarjan()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
		//	cout<<u<<"=="<<v<<endl;
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		void build()
		{
			for(int i=0;i<nn;i++)	if(vis[i]==0)	dfs1(i);
			for(int i=0;i<nn;i++)	if(bsz[bfa[i]]>1)	fob[i]=1;
		}
}ta;
class Dinic
{
	private:
		class Edge
		{
			public:	int v,c,nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int lev[maxn];
		int bfs()
		{
			queue <int> que;	que.push(sta);
			memset(lev,0,sizeof lev);	lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(lev[v]==0&&c)
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
			for(int i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[u]+1==lev[v]&&c)
				{
					int cc=min(lc-nc,c);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			if(nc==0)	lev[u]=-1;
			return nc;
		}
	public:
		Dinic()
		{
			memset(pre,-1,sizeof pre);
		}
		int sta,end;
		void addedge(int u,int v,int c)
		{
		//	cout<<u<<"="<<v<<"="<<c<<endl;
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		int work()
		{
			int ans=0;
			while(bfs())
			{
				int t;
				do
				{
					t=dfs(sta,oo);
					ans+=t;
				}while(t);
			}
			return ans;
		}
}di;
int main()
{
	scanf("%d%d",&n,&m);	nn=n*m; 
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			int pos=i*m+j,w;
			scanf("%d",&sco[pos]);
			scanf("%d",&w);
			for(int k=0;k<w;k++)
			{
				int a,b;	scanf("%d%d",&a,&b);
				ta.addedge(a*m+b,pos);
				dis[a*m+b][pos]=1;
			}
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<j;k++)
			{
				ta.addedge(i*m+k,i*m+j);
				dis[i*m+k][i*m+j]=1;
			}
	ta.build();
//	for(int i=0;i<nn;i++)	cout<<i<<" "<<ta.bsz[ta.bfa[i]]<<endl;
	for(int k=0;k<nn;k++)
		for(int i=0;i<nn;i++)
			for(int j=0;j<nn;j++)
				if(dis[i][k]&&dis[k][j])	dis[i][j]=1;
	
	for(int i=0;i<nn;i++)
		for(int j=0;j<nn;j++)	if(dis[i][j]&&ta.fob[j])	ta.fob[i]=1;
		
	for(int i=0;i<nn;i++)	if(ta.fob[i])
		for(int j=0;j<nn;j++)	dis[i][j]=dis[j][i]=0; 
	
	di.sta=nn;	di.end=nn+1;
	for(int i=0;i<nn;i++)	if(ta.fob[i]==0)
	{
		if(sco[i]>=0)	di.addedge(di.sta,i,sco[i]),sum+=sco[i];
		else			di.addedge(i,di.end,-sco[i]);
	}
	for(int i=0;i<nn;i++)
		for(int j=0;j<nn;j++)	if(dis[i][j])
			di.addedge(i,j,oo);
			
	//for(int i=0;i<nn;i++)
	//	for(int j=0;j<nn;j++)	if(dis[i][j]&&dis[j][i])	cout<<i<<"==="<<j<<endl;
	//cout<<"===="<<endl;
	
	cout<<sum<<endl;
	printf("%d\n",max(0,sum-di.work()));
}
