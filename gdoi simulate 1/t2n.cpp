#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=5000000;
struct Edge
{
	int v,c,p;
	int nxt;
}e[400];
int pre[20],en=0;
void addedge(int u,int v,int c,int p)
{
	e[en].v=v;e[en].c=c;e[en].p=p;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].p=p;e[en].nxt=pre[v];pre[v]=en++;
}
int n,k,m;
int dyp[maxn];
bool vis[maxn];
int fyp[maxn];
int dis[15][15];
int mul[15];
int mar[15];
int end=0;
int ans=0;
void init()
{
	mul[0]=1;
	for(int i=1;i<15;i++)	mul[i]=mul[i-1]*3; 
}
void dfs(int con)
{
	if(vis[con]==1)	return;
	else
	{
		vis[con]=1;
		int flag=0,cnt=0;
		for(int i=1;i<=n;i++)	if(mar[i]==1)
		{
			if((con/mul[i])%3==0)
			{	flag=1;	break;	}
			if((con/mul[i])%3==1)	cnt++;
		}
		if(flag==0&&cnt%2==0)
		{
			for(int i=con;i<=end;i++)	fyp[i]=1e9;
			fyp[con]=0;
			for(int i=con;i<=end;i++)	if(fyp[i]!=1e9&&fyp[i]<dyp[con])
			{
				
				for(int u=1;u<=n;u++)
					for(int v=1;v<=n;v++)	if((i/mul[u])%3==1||(i/mul[v])%3==1)
					{
						int tmp=i;
						if((tmp/mul[u])%3<2)	tmp+=mul[u];	else	tmp-=mul[u];
						if((tmp/mul[v])%3<2)	tmp+=mul[v];	else	tmp-=mul[v];
						if(tmp<mul[n+1])	fyp[tmp]=min(fyp[tmp],fyp[i]+dis[u][v]);
					}
			}
		//	cout<<end<<"="<<fyp[end]<<endl;
			dyp[con]=fyp[end];
			return;
		}
		
		for(int u=1;u<=n;u++)	if(mar[u]==1&&(con/mul[u])%3==0)
		{
			int flag=0,tmp=con;
			if(mar[u]==1)
			{
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,p=e[i].p;
					if((con/mul[v])%3&&p==1)
					{
						flag=1;
						if((tmp/mul[u])%3<2)	tmp+=mul[u];	else	tmp-=mul[u];;
						if((tmp/mul[v])%3<2)	tmp+=mul[v];	else	tmp-=mul[v];
						if(tmp>mul[n+1])	break;
					}
				}
			}
			if(flag==1)
			{
				if(tmp<mul[n+1])	dfs(tmp),dyp[con]=min(dyp[con],dyp[tmp]); 
			}
			else
			{
				for(int v=1;v<=n;v++)	if((con/mul[v])%3)
				{
					int tmp=con;
					if((tmp/mul[u])%3<2)	tmp+=mul[u];	else	tmp-=mul[u];
					if((tmp/mul[v])%3<2)	tmp+=mul[v];	else	tmp-=mul[v];
					if(tmp<mul[n+1]&&dis[u][v]<dyp[con])	dfs(tmp),dyp[con]=min(dyp[con],dyp[tmp]+dis[u][v]);
				}
			}
		}
	}
	return;
}
int main()
{
//	freopen("food7.in","r",stdin);
	init();
	cin>>n>>k;
	memset(pre,-1,sizeof pre);
	for(int i=0;i<15;i++)	for(int j=0;j<15;j++)	dis[i][j]=1e9;
	mar[1]=1;
	for(int i=0;i<k;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		mar[u]=mar[v]=1;
		dis[u][v]=dis[v][u]=min(dis[u][v],c);
		addedge(u,v,c,1);
		ans+=c;
	}
	for(int i=1;i<=n;i++)	if(mar[i])	end+=mul[i]*2;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		dis[u][v]=dis[v][u]=min(dis[u][v],c);
		addedge(u,v,c,0);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=0;i<maxn;i++)	dyp[i]=1e9;
	dfs(6);
	cout<<dyp[6]+ans<<endl;
}
