#include<iostream>
#include<stack>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
struct Edge
{
	int v;
	int next;
}e[50000];
int en=0;
int pre[5000];
int vis[5000];
int lev[5000];
int fa[5000];
int s[5000];
int w[5000];
int ma[5000];
void addedge(int u,int v)
{
	e[en].v=v;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].next=pre[v];pre[v]=en++;
}
void dfs(int u,int f,int l)
{
	lev[u]=l;
	vis[u]=1;
	fa[u]=f;
	for(int i=pre[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(vis[v]==0) dfs(v,u,l+1);
	}
}
int getvec(int u,int v)
{
	int ut=u,vt=v;
	while(lev[ut]<lev[vt]) vt=fa[vt];
	while(lev[ut]>lev[vt]) ut=fa[ut];
	while(ut!=vt) vt=fa[vt],ut=fa[ut];
	int root=vt;
	
	ut=u,vt=v;
	int cnt=0;
	while(ut!=root) s[cnt++]=w[ut],ut=fa[ut];
	s[cnt++]=w[root]; 
	stack <int> q;
	while(vt!=root) q.push(w[vt]),vt=fa[vt];
	while(!q.empty()) s[cnt++]=q.top(),q.pop();
	
	return cnt;
}
int n,m;
int main()
{
	memset(pre,-1,sizeof pre);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v); addedge(u,v);
	}
	dfs(1,-1,0);
	
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		int len=getvec(u,v);
		int cur1=0;
		for(int i=0;i<len;i++)
		{
			int t=lower_bound(ma,ma+cur1,s[i])-ma;
			if(t>=cur1) cur1++;
			ma[t]=s[i];
		}
		reverse(s,s+len);
		int cur2=0;
		for(int i=0;i<len;i++)
		{
			int t=lower_bound(ma,ma+cur2,s[i])-ma;
			if(t>=cur2) cur2++;
			ma[t]=s[i];
		}
		printf("%d\n",max(cur1,cur2));
	}
}
