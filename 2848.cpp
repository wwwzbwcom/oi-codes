#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000;
const int oo=1e9;
struct ZKW
{
	ZKW()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	struct Edge
	{
		int v,c,f;
		int nxt;
	}e[maxn*maxn*2];
	int pre[maxn],en;
	int vis[maxn];
	int sta,end,n;
	int cfee;
	int tfee;
	void addedge(int u,int v,int c,int f)
	{
	//	cout<<u<<"="<<v<<" "<<c<<" "<<f<<endl; 
		e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
	}
	int dfs(int u,int lc)
	{
		if(u==end)
		{
		//	cout<<cfee<<endl;
			tfee+=lc*cfee;
			return lc;
		}
		int nc=0;
		vis[u]=1;
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c,f=e[i].f;
			if(!vis[v]&&c&&!f)
			{
				int cc=min(c,lc-nc);	cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		return nc;
	}
	bool updatedis()
	{
		int mni=oo;
		for(int u=1;u<=n;u++)	if(vis[u])
		{
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&f<mni)	mni=f;
			}
		}
	//	cout<<mni<<endl;
		if(mni==oo)	return 0;
		
		for(int u=1;u<=n;u++)	if(vis[u])
			for(int i=pre[u];i!=-1;i=e[i].nxt)
				e[i].f-=mni,e[i^1].f+=mni;
		cfee+=mni;
		return 1;
	}
	void zkw()
	{
		do
		{
			do	memset(vis,0,sizeof vis);	while(dfs(sta,oo));
		}while(updatedis());
	}
}z;
int m,n;
int main()
{
	scanf("%d%d",&m,&n);
	z.sta=m*n+n+1;
	z.end=m*n+n+2;
	z.n=m*n+n+2;
	for(int i=1;i<=m;i++)	for(int j=1;j<=n;j++)	z.addedge(n+(i-1)*n+j,z.end,1,0);
	for(int i=1;i<=n;i++)	z.addedge(z.sta,i,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int fee;	scanf("%d",&fee);
			for(int k=1;k<=n;k++)	z.addedge(i,n+(j-1)*n+k,1,k*fee);
		}
	z.zkw();
	printf("%.2lf",(double)z.tfee/(double)n);
}
