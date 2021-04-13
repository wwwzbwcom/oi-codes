#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=1000100;
struct Edge
{
	int v,nxt;
}e[maxn*2];
int pre[maxn],en=0;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
int n;
long long sum[maxn],cnt[maxn];
long long res[maxn];
int p;
void dfs1(int u,int f)
{
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f)
		{
			dfs1(v,u);
			sum[u]+=sum[v];
			cnt[u]+=cnt[v];
		}
	}
	sum[u]+=cnt[u];
	cnt[u]++; 
	
}
void dfs2(int u,int f,long long s,long long c)
{
//	cout<<u<<"="<<f<<" "<<s<<"="<<c<<" "<<sum[u]<<endl;
	s+=c;
	res[u]=sum[u]+s;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f)
		{
			dfs2(v,u,s+(sum[u]-sum[v])-cnt[v],c+(cnt[u]-cnt[v]));
		}
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	dfs1(1,-1);
	dfs2(1,-1,0,0);
	for(int i=1;i<=n;i++)
		if(res[p]<res[i])	p=i;
	printf("%d\n",p);
}
