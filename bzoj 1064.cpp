#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100100;
int n,m;
int gcd(int a,int b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
class Graph
{
	private: 
		class Edge
		{
			public:	int v,c,nxt;
		}e[maxn*20];
		int pre[maxn],en;
		int vis[maxn],dis[maxn];
		int bmn[maxn],bmx[maxn],bn;
		int cir[maxn*40],cn;
		void dfs(int u,int fe,int l)
		{
			vis[u]=1;	dis[u]=l;	bmn[bn]=min(bmn[bn],l);	bmx[bn]=max(bmx[bn],l);
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(i/2!=fe/2)
				{
					if(vis[v])
					{
						if(abs((l+c)-dis[v]))	cir[++cn]=abs((l+c)-dis[v]);
					} 
					else	dfs(v,i,l+c);
				}
			}
		}
	public:
		Graph()
		{
			memset(pre,-1,sizeof pre);
			for(int i=0;i<maxn;i++)	bmn[i]=1e9,bmx[i]=-1e9;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].c= 1;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=-1;e[en].nxt=pre[v];pre[v]=en++;
		}
		void work()
		{
			for(int i=1;i<=n;i++)	if(vis[i]==0)	bn++,dfs(i,-10,0);
			if(cn==0)
			{
				int ans=0;
				for(int i=1;i<=bn;i++)	ans+=(bmx[i]-bmn[i]+1);
				if(ans>=3)	printf("%d %d\n",ans,3);
				else	printf("%d %d\n",-1,-1);
			}
			else
			{
				int ans1=cir[1];
				for(int i=2;i<=cn;i++)	ans1=gcd(ans1,cir[i]);
				int ans2=ans1;
				for(int i=3;i<=ans1;i++)	if(ans1%i==0)	{	ans2=i;	break;	}
				if(ans1<3)	printf("%d %d\n",-1,-1); 
				else	printf("%d %d\n",ans1,ans2);
			}
		}
}gp;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(u,v);
	}
	gp.work();
}
