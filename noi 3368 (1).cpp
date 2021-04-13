#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int oo=1e9;
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c,f;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		int pfee;
		int dfs(int u,int lc)
		{
			//cout<<u<<endl;
			if(u==end)
			{
			//	cout<<pfee<<"="<<lc<<endl; 
				tfee+=pfee*lc;
				return lc;
			}
			int nc=0;
			vis[u]=1;
			for(register int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					int cc=min(lc-nc,c);
					cc=dfs(v,cc);
					if(cc)
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			return nc;
		}
		inline bool getdis()
		{
			int mni=oo;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,f);
				}
			if(mni==oo)	return 0;
			pfee+=mni;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			return 1;
		}
	public:
		int sta,end;
		int tfee,flo;
		ZKW()
		{
			memset(pre,-1,sizeof pre);
		}
		inline void addedge(int u,int v,int c,int f)
		{
			e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
		}
		void zkw()
		{
			do
			{
				int t;
				do
				{
					memset(vis,0,sizeof vis);
					t=dfs(sta,oo);
					flo+=t;
				}while(t);
			}while(getdis());
		}
}zk;
int n,m;
int dis[maxn][maxn];
int main()
{
	scanf("%d%d",&n,&m);	n++;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			dis[i][j]=1e9;
	for(int i=0;i<n;i++)	dis[i][i]=0;
	for(int i=0;i<m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		dis[u][v]=dis[v][u]=min(dis[u][v],c);
	}
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	
	zk.sta=n+(n+1)+1;	zk.end=n+(n+1)+2;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(dis[i][j]<oo)
				zk.addedge(i+(n+1),j,1,dis[i][j]);
	for(int i=0;i<n;i++)	zk.addedge(i,zk.end,1,0),zk.addedge(zk.sta,i+(n+1),1,0);
	zk.addedge(n,zk.end,3,0),zk.addedge(zk.sta,n+(n+1),3,0);
	zk.addedge(0,0+(n+1),2,0);
	
	zk.addedge(0+(n+1),n,3,0);
	for(int i=1;i<n;i++)	zk.addedge(i+(n+1),n,1,dis[i][0]);
	zk.addedge(n+(n+1),0,3,0);
	
	zk.zkw();
	printf("%d\n",zk.tfee);
}
