#include<iostream>
#include<cstring>
using namespace std;
const int maxn=2100;
int n,k,cc;
int sum;
struct TREE
{
	struct EDGE
	{
		int v,c,nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int dis[maxn];
	void init()
	{
		memset(pre,-1,sizeof pre);	en=0;
		memset(dis,0,sizeof dis);
	}
	void addedge(int u,int v,int c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
	}
	void dfs1(int u,int f,int d)
	{
		dis[u]=d;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(v!=f)	dfs1(v,u,d+c);
		}
	}
	void dfs2(int u,int f)
	{
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(v!=f)
			{
				if(dis[v]+c==dis[u])
				{
					e[i].c=e[i^1].c=0;
					dfs2(v,u);
				}
			}
		}
	}
	void work()
	{
		int p1,p2;
		for(int i=1;i<=k;i++)
		{
			p1=-1;	dfs1(0,-1,0);
			for(int j=1;j<=n;j++)	if(p1==-1||dis[p1]<dis[j])	p1=j;
			p2=-1;	dfs1(p1,-1,0);
			for(int j=1;j<=n;j++)	if(p2==-1||dis[p2]<dis[j])	p2=j;
			
		//	cout<<p1<<"="<<p2<<" "<<dis[p2]<<endl;
			if(dis[p2]>cc)	sum=sum-(dis[p2]-cc);	else	break;
			dfs2(p2,-1);
		}
	}
}tr;
int main()
{
	freopen("ex_mzz2.in","r",stdin);
	while(cin>>n>>k>>cc)
	{
		tr.init();
		sum=0;
		for(int i=0;i<n-1;i++)
		{
			int u,v,w;	cin>>u>>v>>w;
			tr.addedge(u,v,w);
			sum+=2*w;
		}
		tr.work();
		cout<<sum<<endl;
	}
}
