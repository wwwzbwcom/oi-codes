#include<iostream>
#include<cstring> 
using namespace std;
const int maxn=11100;
const int oo=1e9;
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c,f;
				int nxt;
		}e[maxn*2+10000*1000];
		int pre[maxn],en;
		int vis[maxn];
		int dfs(int u,int lc)
		{
			if(u==end)
			{
				tfee+=pfee*lc;
				return lc;
			}
			int nc=0;	vis[u]=1;
			for(int i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					int cc=min(c,lc-nc);
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
			long long mni=1e15;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,(long long)f);
				}
			if(mni==1e15)	return 0;
			pfee+=mni;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			return 1;
		}
	public:
		int sta,end;
		int flo;
		long long pfee,tfee;
		ZKW()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c,int f)
		{
			e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
		}
		void work()
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
int main()
{
	cin>>n>>m;
	zk.sta=n+m+1;
	zk.end=n+m+2;
	for(int i=1;i<=n;i++)
	{
		int a;	cin>>a;
		zk.addedge(zk.sta,i,a,0);
	}
	for(int i=1;i<=m;i++)
	{
		int s,t,c;	cin>>s>>t>>c;
		zk.addedge(n+i,zk.end,oo,0);
		for(int j=s;j<=t;j++)	zk.addedge(j,n+i,oo,c);
	}
	zk.work();
	cout<<zk.flo<<endl;
	cout<<zk.tfee<<endl;
}
