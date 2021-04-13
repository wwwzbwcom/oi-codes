#include<algorithm>
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
const int oo=1e8;
struct Graph
{
	Graph(){n=0;memset(p,-1,sizeof p);}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[60100];
	int p[500],n;
	void ae(int u,int v,int c)
	{
		e[n].v=v;e[n].c=c;e[n].nxt=p[u];p[u]=n++;
	}
}f,b;
int n,m;
int qn;
int dyp[410][410];
int aid[410][410][130];
queue <int> uq,vq,cq;
void work()
{
	while(!cq.empty())
	{
		int u=uq.front(),v=vq.front(),c=cq.front();
		uq.pop();vq.pop();cq.pop();
	//	cout<<u<<" "<<v<<" "<<c<<endl;
		if(c==0)
		{
			for(int i=f.p[v];i!=-1;i=f.e[i].nxt)
			{
				int nv=f.e[i].v,c=f.e[i].c;
				if(aid[u][nv][c]>dyp[u][v]+1)
				{
					aid[u][nv][c]=dyp[u][v]+1;
					uq.push(u),vq.push(nv),cq.push(c);
				}
			}
		}
		else
		{
			for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
			{
				int nu=b.e[i].v;
				if(c==b.e[i].c)
				{
					if(dyp[nu][v]>aid[u][v][c]+1)
					{
						dyp[nu][v]=aid[u][v][c]+1;
						uq.push(nu),vq.push(v),cq.push(0);
					}
				}
			}
		}
	}
}
int main()
{
//	freopen("baj71.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v; char c[10];	scanf("%d%d%s",&u,&v,c);
		f.ae(u,v,c[0]);
		b.ae(v,u,c[0]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			dyp[i][j]=oo;
			for(int k=1;k<=150;k++)	aid[i][j][k]=oo;
		}
	for(int i=1;i<=n;i++)	uq.push(i),vq.push(i),cq.push(0),dyp[i][i]=0;
	for(int u=1;u<=n;u++)
		for(int i=f.p[u];i!=-1;i=f.e[i].nxt)
		{
			int v=f.e[i].v;
			uq.push(u),vq.push(v),cq.push(0),dyp[u][v]=1;
		}
	work();
	scanf("%d",&qn);
	int u,v;
	for(int q=1;q<=qn;q++)
	{
		scanf("%d",&v);
		if(q!=1)
		{
			if(dyp[u][v]==oo)	printf("-1\n");
			else	printf("%d\n",dyp[u][v]);
		}
		u=v;
	}
}
