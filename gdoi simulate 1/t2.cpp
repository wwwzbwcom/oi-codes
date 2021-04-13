#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
struct Edge
{
	int v,c,p;
	int nxt;
}e[200];
int pre[20],en=0;
void addedge(int u,int v,int c,int p)
{
	e[en].v=v;e[en].c=c;e[en].p=p;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].p=p;e[en].nxt=pre[v];pre[v]=en++;
}
int n,k,m;
int dyp[8][3000000];
bool vis[8][3000000];
void SPFA()
{
	queue <int> quu,quc;	memset(vis,0,sizeof vis); 	for(int i=0;i<8;i++)	for(int j=0;j<2100000;j++)	dyp[i][j]=1e9;
	quu.push(1);	quc.push(0);	vis[1][0]=1;	dyp[1][0]=0;
	
	while(!quu.empty())
	{
		int u=quu.front(),cou=quc.front();		quu.pop();	quc.pop();
		vis[u][cou]=0;
	//	cout<<u<<" "<<cou<<" "<<dyp[u][cou]<<" "<<dyp[1][7]<<endl;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,cov=cou,c=e[i].c,p=e[i].p;
			if(p!=-1)	cov=cou|(1<<p);
			if(cov<3000000&&dyp[v][cov]>dyp[u][cou]+c)
			{
				dyp[v][cov]=dyp[u][cou]+c;
				if(vis[v][cov]==0)
				{
					vis[v][cov]=1;
					quu.push(v);
					quc.push(cov);
				}
			}
		}
	}
}
int main()
{
	cin>>n>>k;
	memset(pre,-1,sizeof pre);
	for(int i=0;i<k;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		addedge(u,v,c,i);
	}
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		addedge(u,v,c,-1);
	}
	SPFA();
	cout<<dyp[1][(1<<k)-1];
}
