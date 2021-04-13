#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=500500;
int n,s;
struct TREE
{
	struct EDGE
	{
		int v,c;
		int nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int dis[4][maxn];
	int boo[maxn];
	int vis[maxn];
	TREE()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	void addedge(int u,int v,int c)
	{
		e[en].v=v;	e[en].c=c;	e[en].nxt=pre[u];	pre[u]=en++;
		e[en].v=u;	e[en].c=c;	e[en].nxt=pre[v];	pre[v]=en++;
	}
	void dfs(int u,int f,int d,int mod)
	{
		if(mod==3&&boo[u]) d=0;
		dis[mod][u]=d;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(v!=f)	dfs(v,u,d+c,mod);
		}
	} 
	void work()
	{
		int u;
		dfs(1,0,0,0);
		u=0;	for(int i=1;i<=n;i++)	if(dis[0][i]>=dis[0][u])	u=i;
		dfs(u,0,0,1);
		u=0;	for(int i=1;i<=n;i++)	if(dis[1][i]>=dis[1][u])	u=i;
		dfs(u,0,0,2);
		u=0;	for(int i=1;i<=n;i++)	if(u==0||max(dis[1][i],dis[2][i])<=max(dis[1][u],dis[2][u]))	u=i;
		boo[u]=1;
		int um[2],cm[2];	um[0]=um[1]=cm[0]=cm[1]=0;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(um[0]==0||min(dis[1][v],dis[2][v])<=min(dis[1][um[0]],dis[2][um[0]]))	um[1]=um[0],cm[1]=cm[0],um[0]=v,cm[0]=c;
			else	if(um[1]==0||min(dis[1][v],dis[2][v])<=min(dis[1][um[1]],dis[2][um[1]]))	um[1]=v,cm[1]=c;
		}
		if(min(dis[1][um[0]],dis[2][um[0]])+cm[0]<min(dis[1][um[1]],dis[2][um[1]])+cm[1])	swap(um[0],um[1]),swap(cm[0],cm[1]);
		while(1)
		{
			int flag=0;
			int cnt=0;
		//	cout<<um[0]<<"="<<um[1]<<" "<<cm[0]<<"="<<cm[1]<<endl;
			for(int k=0;k<2;k++)	if(s>=cm[k]&&um[k]!=0)
			{
				s-=cm[k];	boo[um[k]]=1;	flag=1;
				int u=um[k];	um[k]=0;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(um[k]==0||min(dis[1][v],dis[2][v])<=min(dis[1][um[k]],dis[2][um[k]]))	um[k]=v,cm[k]=c;
				}
			}
			cnt++;
			if(cnt>n)	int a=1/0;
			if(min(dis[1][um[0]],dis[2][um[0]])+cm[0]<min(dis[1][um[1]],dis[2][um[1]])+cm[1])	swap(um[0],um[1]),swap(cm[0],cm[1]);
			if(flag==0)	break;
		}
		int ans=0;
		for(int i=1;i<=n;i++)	if(boo[i])	{dfs(i,0,0,3);	break;}
		for(int i=1;i<=n;i++)	ans=max(ans,dis[3][i]);
		printf("%d\n",ans); 
	}
}tr;
int main()
{
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n-1;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		tr.addedge(u,v,c);
	}
	tr.work();
}
