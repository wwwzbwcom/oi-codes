#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200100;
int n,m;
class Tree
{
	private:
		class Edge
		{
			public:	int v,c,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int rad[3];
		long long dis[3][maxn];
		void dfs(int u,int f,long long d,int p)
		{
		//	cout<<p<<" "<<d<<endl;
			dis[p][u]=d;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)	dfs(v,u,d+c,p);
			}
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		long long work()
		{
			dfs(1,-1,0,0);
			for(int i=1;i<=n;i++)	if(dis[0][i]>dis[0][rad[1]])	rad[1]=i;
		//	cout<<rad[1]<<endl;
			dfs(rad[1],-1,0,1);
			for(int i=1;i<=n;i++)	if(dis[1][i]>dis[1][rad[2]])	rad[2]=i;
			dfs(rad[2],-1,0,2);
			long long mxa=0;
			for(int i=1;i<=n;i++)	if(min(dis[1][i],dis[2][i])>mxa)	mxa=min(dis[1][i],dis[2][i]);
		//	cout<<rad[1]<<" "<<dis[1][5]<<endl;
			return	dis[1][rad[2]]+mxa;
		}
}tr;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		tr.addedge(u,v,c);
	}
	printf("%lld",tr.work());
}
