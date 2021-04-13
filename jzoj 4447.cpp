#include<iostream> 
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int mod=1e9+7;
const int maxn=3000;
int n,m,t;
class SPFA
{
	private:
		class Edge
		{
			public:
				int v,c;
				int nxt;
		}e[maxn*4];
		int pre[maxn],en;
		int vis[maxn][maxn];
		int dis[maxn][maxn];
	public:
		SPFA()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		void spfa()
		{
			for(int i=0;i<maxn;i++)
				for(int j=0;j<maxn;j++)
					dis[i][j]=1e9;
			queue <int> quu,qud;
			quu.push(1);	qud.push(0);	dis[1][0]=0;	vis[1][0]=1;
			while(!quu.empty())
			{
				int u=quu.front(),d=qud.front();	quu.pop(),qud.pop();	vis[u][d]=0;
				if(d+1>=maxn)	continue;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(dis[v][d+1]>dis[u][d]+c)
					{
						dis[v][d+1]=dis[u][d]+c;
						if(vis[v][d+1]==0)
						{
							vis[v][d+1]=1;
							quu.push(v);	qud.push(d+1);
						}
					}
				}
			}
		}
		int work()
		{
			int ans=0;
			for(int i=1;i<=n;i++)
			{
				int tp=0,j;
				long long fix=1;
				for(j=maxn-1;j>=0;j--)
				{
				//	cout<<tp<<" "<<j<<" "<<dis[i][j]<<" "<<dis[i][j-1]<<endl;
					if(j==0||dis[i][j-1]==1e9||(dis[i][j-1]-dis[i][j])>=t)
					{
					//	cout<<i<<"="<<tp<<"="<<t<<endl;
						ans+=(fix*(t-tp+1)*dis[i][j])%(fix*mod);
						ans%=mod;
						ans+=((fix*(tp+t)*(t-tp+1)/2)%(fix*mod)*j)%(fix*mod);
						ans%=mod;
						tp=t+1;
						break;
					}
					else
					{
						int te=dis[i][j-1]-dis[i][j];
						if(te<=tp)	continue;
						ans+=(fix*(te-tp+1)*dis[i][j])%(fix*mod);
						ans%=mod;
						ans+=((fix*(tp+te)*(te-tp+1)/2)%(fix*mod)*j)%(fix*mod);
						ans%=mod;
						tp=te+1;
					}
				}
			//	cout<<tp<<" "<<t<<" "<<i<<" "<<ans<<endl; 
			}
			return ans;
		}
}sp;
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)	sp.addedge(i,i,0);
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		sp.addedge(u,v,c);
	}
	sp.spfa();
	printf("%d\n",sp.work()); 
} 
