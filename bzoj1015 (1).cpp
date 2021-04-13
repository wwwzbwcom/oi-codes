#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int v;
	int next;
}e[500000];
int pre[1000000],en=0;
int destroy[1000000];
int book[10000000];
int bf[1000000];
int fa[1000000];
int output[1000000];
int n,m,q;
int ans=0;
void addedge(int u,int v)
{
	e[en].v=v;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].next=pre[v];pre[v]=en++;
}
int find(int u)
{
	if(fa[u]==u) return u;
	else return fa[u]=find(fa[u]);
}
int main()
{
	memset(pre,-1,sizeof pre);
	for(int i=0;i<1000000;i++) fa[i]=i;
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int u,v;
		cin>>u>>v;
		addedge(u,v);
	}
	cin>>q;
	for(int i=1;i<=q;i++) cin>>destroy[i],book[destroy[i]]=1;
	
	for(int u=0;u<n;u++)
	{
		if(book[u]==0)
			for(int i=pre[u];i!=-1;i=e[i].next)
			{
				int v=e[i].v;
				if(book[v]==0)
				{
				//	cout<<u<<" "<<v<<endl;
					if(find(v)!=find(u)) fa[find(v)]=find(u);
				}
			}
	}
	
	for(int i=0;i<n;i++) if(bf[find(i)]==0) bf[find(i)]=1,ans++;
	for(int k=1;k<=q;k++)
	{
		int u=destroy[k];
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v;
			if(find(v)!=find(u)) fa[find(v)]=find(u),ans--;
		}
		output[k]=ans;
	}
	for(int i=q;i>=1;i--) cout<<output[i]<<endl;
}
