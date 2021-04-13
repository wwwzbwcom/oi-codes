#include<iostream>
#include<cstring>
using namespace std;
const int maxn=600;
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c;
				long long f;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		long long pfee;
		int dfs(int u,int lc)
		{
			if(u==end)
			{
				tfee+=lc*pfee;
				return lc;
			}
			int nc=0;
			vis[u]=1;
			for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;	long long f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					int cc=min(lc-nc,c);
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
			long long mni=1e18;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;	long long f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,f);
				}
			if(mni==1e18)	return 0;
			pfee+=mni;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			return 1;
		}
	public:
		int sta,end;
		long long tfee;
		int flo;
		ZKW()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int  v,int c,long long f)
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
					t=dfs(sta,1e9);
					flo+=t;
				}while(t);
			}while(getdis());
		}
}zk;
int fee[maxn];
int main()
{
	int n,m;	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>fee[i];
	zk.sta=n+n*m+1;	zk.end=n+n*m+2;
	for(int i=1;i<=n;i++)	zk.addedge(zk.sta,i,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			zk.addedge(n+(i-1)*m+j,zk.end,1,0);
	for(int i=1;i<=n;i++)
	{
		int p;	cin>>p;
		for(int j=1;j<=p;j++)
		{
			int v;	cin>>v;
			for(int k=1;k<=n;k++)	zk.addedge(i,n+(k-1)*m+v,1,(long long)fee[i]*((1ll<<(k))-1ll));
		}
	}
	zk.zkw();
	cout<<zk.tfee<<endl;
}
