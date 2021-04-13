#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200100;
class Graph
{
	private:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*10*2];	
		int pre[maxn],en;
	public:
		int vis[maxn];
		void init()
		{
			memset(vis,0,sizeof vis);
			memset(pre,-1,sizeof pre);
			en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		void bfs(int u)
		{
			queue <int> que;
			if(vis[u]==1)	return;
			que.push(u);	vis[u]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					if(vis[v]==0)
					{
						vis[v]=1;
						que.push(v);
					}
				}
			}
		}
}f,b;
int gn;
int n,m;
int boo[maxn];
int main()
{
	scanf("%d",&gn);
	while(gn--)
	{
		memset(boo,0,sizeof boo);
		f.init();	b.init();
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
			for(int j=1;j<=6;j++)
				f.addedge(i*2+1,((i+j)%n)*2),
				b.addedge(((i+j)%n)*2,i*2+1);
		
		for(int i=0;i<m;i++)
		{
			int u,v;	scanf("%d%d",&u,&v);
			boo[u]=1;
			f.addedge(u*2,v*2+1);
			b.addedge(v*2+1,u*2);
		}
		
		for(int i=0;i<n;i++)	if(boo[i]==0)
		{
			f.addedge(i*2,i*2+1);
			b.addedge(i*2+1,i*2);
		}
		
		f.bfs(0*2);
		b.bfs((n-1)*2);
		b.bfs((n-1)*2+1);
		int flag=0;
		for(int i=0;i<2*n;i++)	if(f.vis[i]&&!b.vis[i])	flag=1;
		if(flag==1)	printf("YES\n");
		else	printf("NO\n");
	}
}
