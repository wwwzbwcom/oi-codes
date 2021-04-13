#include<iostream>
#include<cstring>
using namespace std;
const int maxn=2100;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int pre[maxn],en=0;
int n,k; 
int siz[maxn];
long long dyp[maxn][maxn];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs(int u,int f)
{
	siz[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)
		{
			dfs(v,u);
			for(int p=siz[u];p>=0;p--)
			{
				for(int q=1;q<=siz[v];q++)
					dyp[u][p+q]=max(dyp[u][p+q],dyp[u][p]+dyp[v][q]+(long long)q*(k-q)*c+(long long)(siz[v]-q)*((n-k)-(siz[v]-q))*c);
				dyp[u][p]=dyp[u][p]+dyp[v][0]+(long long)siz[v]*(n-k-siz[v])*c;
			}
			siz[u]+=siz[v];
		}
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>k;
	for(int i=1;i<=n-1;i++)
	{
		int u,v,c;	cin>>u>>v>>c; 
		addedge(u,v,c);
	}
	dfs(1,0);
	cout<<dyp[1][k]<<endl;
}
