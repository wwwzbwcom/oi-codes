#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue> 
using namespace std;
const int maxn=10100;
const int oo=1e9;
class Dinic
{
	private:
		class Edge
		{
			public:
				int v,c;
				int nxt;
		}e[1000000*2];
		int pre[maxn],en;
		int lev[maxn];
		
		bool bfs()
		{
			queue <int> que;	memset(lev,-1,sizeof lev);
			que.push(sta);	lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
			//	cout<<u<<endl;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
				//	cout<<v<<" "<<c<<" "<<lev[v]<<endl;
					if(lev[v]==-1&&c)
					{
					//	cout<<v<<"="<<c<<endl;
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
					int cc=min(lc-nc,c);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			if(!nc)	lev[u]=-1;
			return nc;
		}
	public:
		Dinic()
		{
			memset(pre,-1,sizeof pre);
			en=0;
		}
		int sta,end;
		void addedge(int u,int v,int c)
		{
		//	cout<<u<<"="<<v<<"="<<c<<endl;
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		int dinic()
		{
			int ans=0;
			while(bfs())	ans+=dfs(sta,oo);
			return ans;
		}
}d;
int n,m,k;
int sum;
int main()
{
	freopen("work.in","r",stdin);
	freopen("work.out","w",stdout);
	cin>>n>>m>>k;
	d.sta=n+k+1;	d.end=n+k+2;
	for(int i=1;i<=n;i++)
	{
		int val;	cin>>val;
		d.addedge(d.sta,i,val);	sum+=val;
	}
	for(int i=1;i<=n;i++)
	{
		int val;	cin>>val;
		d.addedge(i,d.end,val);	sum+=val;
	}
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		d.addedge(u,v,c);
		d.addedge(v,u,c);
	}
	for(int i=1;i<=k;i++)
	{
		int t,a,b;	cin>>t>>a>>b;
		if(a==0)	d.addedge(d.sta,n+i,b);
		else		d.addedge(n+i,d.end,b);
		sum+=b;
		for(int j=1;j<=t;j++)
		{
			int v;	cin>>v;
			if(a==0)	d.addedge(n+i,v,oo);
			else		d.addedge(v,n+i,oo);
		}
	}
	cout<<sum-d.dinic()<<endl;
}
