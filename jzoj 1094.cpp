#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=100000;
const int oo=1e9;
int n,m;
int map[200][200];
struct ZKW
{
	ZKW()
	{
		memset(pre,-1,sizeof pre);
		en=0;
	}
	struct Edge
	{
		int v,c;
		double f;
		int nxt;
	}e[maxn];
	int pre[maxn],en;
	int vis[maxn];
	int sta,end;
	double per,fee;
	int flo;
	void addedge(int u,int v,int c,double f)
	{
		e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
	}
	int dfs(int u,int lc)
	{
		if(u==end)
		{
			fee+=(double)lc*per;
			return lc;
		}
		int nc=0;
		vis[u]=1;
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;	double f=e[i].f;
			if(c&&abs(f)<1e-10&&!vis[v])
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
		double minf=1e100;
		for(int u=0;u<n+m+2;u++)	if(vis[u])
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;	double f=e[i].f;
				if(!vis[v]&&c&&f<minf)	minf=f;
			}
		if(minf==1e100)	return 0;
		for(int u=0;u<n+m+2;u++)	if(vis[u])
			for(int i=pre[u];i!=-1;i=e[i].nxt)
				e[i].f-=minf,e[i^1].f+=minf;
		per+=minf;
		return 1; 
	}
	int zkw()
	{
		do
		{
			int t;
			do
			{
				memset(vis,0,sizeof vis);
				t=dfs(sta,oo);
				flo+=t;
			}
			while(t);
		}while(getdis());
		return fee;
	}
}z;
int main()
{
	cin>>n>>m;
	z.sta=n+m,z.end=n+m+1;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			int f;	cin>>f;
			if(f!=0)
			z.addedge(i,n+j,1,-log((double)f/double(100)));
		}
	for(int i=0;i<n;i++)
	{
		int c;	cin>>c;
		z.addedge(z.sta,i,c,0);
	}
	for(int i=0;i<m;i++)
	{
		int c;	cin>>c;
		z.addedge(n+i,z.end,c,0);
	}
	z.zkw();
	//cout<<z.flo<<"~~"<<z.fee<<endl;
	for(int u=0;u<n;u++)
		for(int i=z.pre[u];i!=-1;i=z.e[i].nxt)
		{
			int v=z.e[i].v,c=z.e[i].c,f=z.e[i].f;
			if(c==0)	map[u][v-n]=1;
		}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			cout<<map[i][j];
		cout<<endl;
	}
}
