#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
struct Graph
{
	Graph(){n=0;memset(p,-1,sizeof p);}
	struct Edge
	{
		int v,nxt;	
	}e[10000];
	int n;
	int p[10000];
	void ae(int u,int v)
	{e[n].v=v;e[n].nxt=p[u];p[u]=n++;}
}b,a;
int n,p,r;
int val[10000];


stack <int> s; 
int vis[10000],low[10000];
bool instack[10000];
int cnt=0;
int block[10000];
int bn=0;

int nval[10000];
int in[10000];
void tj(int u)
{
	vis[u]=low[u]=++cnt;
	instack[u]=1;	s.push(u);
	for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
	{
		int v=b.e[i].v;
		if(vis[v]==0)
		{
			tj(v);
			low[u]=min(low[u],low[v]);
		}
		else	if(instack[v]==1)	low[u]=min(low[u],vis[v]);
	}
	if(vis[u]==low[u])
	{
		int t;	bn++;
		do
		{
			t=s.top();	instack[t]=0;	s.pop();
			block[t]=bn;
		}while(t!=u);
	}
}
void dfs(int u)
{
	vis[u]=1;
	for(int i=a.p[u];i!=-1;i=a.e[i].nxt)
	{
		int v=a.e[i].v;
		if(vis[v]==0)	dfs(v);
	}
}
void input()
{
	cin>>n>>p;
	for(int i=1;i<=n;i++)	val[i]=2e9;
	for(int i=1;i<=p;i++)
	{
		int pe,va;	cin>>pe>>va;
		val[pe]=va;
	}
	cin>>r;
	for(int i=1;i<=r;i++)
	{
		int u,v;	cin>>u>>v;
		b.ae(u,v);
	}
}
int main()
{
	input();
	for(int u=1;u<=n;u++)	if(vis[u]==0)	tj(u);
	
	for(int i=1;i<=bn;i++)	nval[i]=2e9;
	for(int u=1;u<=n;u++)
		for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
		{
			int v=b.e[i].v;
			if(block[u]!=block[v])	a.ae(block[u],block[v]),in[block[v]]++;//cout<<block[u]<<"~"<<block[v]<<endl;
		}
	for(int i=1;i<=n;i++)	nval[block[i]]=min(nval[block[i]],val[i]);

	
	int ans1=0;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=bn;i++)
		if(in[i]==0&&nval[i]<2e9)
		{
			dfs(i);
			ans1+=nval[i];
		}
	
	int flag=0;
	for(int i=1;i<=n;i++)
		if(vis[block[i]]==0)
		{
			flag=1;	break;
		}
	
	if(flag==0)	cout<<"YES"<<endl<<ans1<<endl;
	else
	{
		int ans2;
		for(int i=1;i<=n;i++)
			if(nval[i]<2e9)	dfs(i);
		for(int i=1;i<=n;i++)
			if(vis[block[i]]==0)
			{
				ans2=i;
				break;
			}
		cout<<"NO"<<endl<<ans2<<endl;
	}
}
