#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=20000;
const int oo=1e8;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
		sta=10001;
		end=10002;
	}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[maxn*20];
	int pre[maxn],en;
	int lev[maxn];
	void addedge(int u,int v,int c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	//	if(u==sta)	cout<<u<<" "<<v<<" "<<pre[u]<<endl;
	}
	int sta,end;
	bool bfs()
	{
		memset(lev,-1,sizeof(lev));	queue <int> que;
		lev[sta]=1;	que.push(sta);
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(c&&lev[v]==-1)
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
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
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
		if(nc==0)	lev[u]=-1;
		return nc;
	}
	int dinic()
	{
		int ans=0;
		while(bfs())
		{
			ans+=dfs(sta,oo);
		}
		return ans;
	}
}d;
int n,m;
int a[200][200];
int b[200][200];
int c[200][200];
int sum;
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>b[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>c[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if((i%2+j%2)%2==0)	d.addedge(d.sta,i*m+j,a[i][j]),d.addedge(i*m+j,d.end,b[i][j]);
			else	d.addedge(i*m+j,d.end,a[i][j]),d.addedge(d.sta,i*m+j,b[i][j]); 
			sum+=a[i][j]+b[i][j];
			for(int p=-1;p<=1;p++)
				for(int q=-1;q<=1;q++)	if(abs(p)+abs(q)==1)
				{
					if(0<=i+p&&i+p<n&&0<=j+q&&j+q<m)
					{
						d.addedge(i*m+j,(i+p)*m+(j+q),c[i][j]);
						d.addedge((i+p)*m+(j+q),i*m+j,c[i][j]);
						sum+=c[i][j];
					}
				}
		}
//	cout<<d.pre[d.sta]<<endl;
	cout<<sum-d.dinic();
}
