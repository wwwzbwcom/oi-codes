#include<iostream>
#include<cstring>
using namespace std;
const int maxn=5100;
int n,m;
int u[maxn],v[maxn],c[maxn];
int ans[maxn];
class Graph
{
	public:
		class Edge
		{
			public:
				int v,c;
				int nxt; 
		}e[maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		void dfs(int u,int ban)
		{
			//cout<<u<<endl;
			vis[u]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(c==0&&i/2!=ban&&vis[v]==0)	dfs(v,ban);	
			}
		}
		Graph()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=0;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		bool judge(int u,int v,int ban)
		{
			memset(vis,0,sizeof vis);
		//	cout<<u<<" "<<v<<" "<<ban<<endl;
			dfs(u,ban);
		//	cout<<"=="<<vis[v]<<endl;
			return vis[v];
		}
}gp;
int main()
{
//	freopen("out.txt","w",stdout);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		cin>>u[i]>>v[i]>>c[i];
		gp.addedge(u[i],v[i],c[i]);
	}
	for(int i=0;i<m;i++)
	{
		if(c[i])	ans[i]=0;
		else
		{
			if(gp.judge(v[i],u[i],i))	ans[i]=0,gp.e[i*2+1].c=1;
			else	ans[i]=1,gp.e[i*2].c=0;
		}
	}
	for(int i=0;i<m;i++)	cout<<ans[i]<<endl;
}
