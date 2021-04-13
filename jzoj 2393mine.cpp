#include<iostream>
#include<cstring>
using namespace std;
const int maxn=500;
const int oo=1e8;
int dis[maxn][maxn];
int n,m,kk;
class ZKW
{
	private:
		class
		{
			public:
				int v,c,f;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		int dfs(int u,int lc)
		{
		//	cout<<u<<"="<<endl;
			if(u==end)
			{
			//	cout<<lc<<" "<<pfee<<endl;
				tfee+=lc*pfee;
				return lc;
			}
			int nc=0;
			vis[u]=1;
			for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					int cc=min(lc,c);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			return nc;
		}
		bool getdis()
		{
			int mni=oo;
			for(int u=0;u<=n*2+2;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,f);
				}
			//	cout<<"="<<mni<<endl;
			if(mni==oo)	return 0;
			for(int u=0;u<=n*2+2;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			pfee+=mni;
			return 1;
		}
	public:
		int sta,end;
		int pfee,tfee;
		int flo;
		ZKW()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v,int c,int f)
		{
			e[en].v=v;	e[en].c=c;	e[en].f= f;	e[en].nxt=pre[u];	pre[u]=en++;
			e[en].v=u;	e[en].c=0;	e[en].f=-f;	e[en].nxt=pre[v];	pre[v]=en++;
		}
		void zkw()
		{
			do
			{
				int tmp;
				do
				{
					memset(vis,0,sizeof vis);
					tmp=dfs(sta,oo);
					flo+=tmp;
				}
				while(tmp);
			}while(getdis());
		}
}zkw;
int main()
{
	cin>>n>>m>>kk;
	for(int i=0;i<maxn;i++)	for(int j=0;j<maxn;j++)	dis[i][j]=oo;
	for(int i=0;i<m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		dis[u][v]=min(dis[u][v],c);
		dis[v][u]=min(dis[v][u],c); 
	}
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)	if(i!=j)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				if(i<j&&k==j&&dis[i][j]!=oo)	zkw.addedge(i*2+1,j*2,1,dis[i][j]);
			}
	zkw.sta=n*2+1;
	zkw.end=n*2+2;
	zkw.addedge(0*2,0*2+1,kk-1,0);
	for(int i=0;i<=n;i++)	zkw.addedge(i*2+1,0*2,1,0);
	for(int i=0;i<=n;i++)	zkw.addedge(zkw.sta,i*2+1,1,0);
	for(int i=1;i<=n;i++)	zkw.addedge(i*2,zkw.end,1,0);
	zkw.zkw();
	if(zkw.flo!=n+3)	while(1);
	cout<<zkw.tfee;
}
