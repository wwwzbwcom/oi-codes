#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio> 
#include<stack>
#include<cmath>
using namespace std;
const int maxn=11000;
class Matrix
{
	public:
		long double m[110][110];
		int y,x;
		long double ans[110];
		void init(int yi,int xi)
		{
			memset(m,0,sizeof m);
			memset(ans,0,sizeof ans);
			y=yi;	x=xi;
		}
		void debug()
		{
			
			cout<<"==============================="<<endl;
			for(int i=0;i<y;i++)
			{
				for(int j=0;j<x;j++)
					cout<<m[i][j]<<" ";
				cout<<endl;
			}
			
		}
		void guass()
		{
			//debug();
			for(int ky=0,kx=0;ky<y&&kx<y;ky++,kx++)
			{
				int p=ky;
				for(int i=ky+1;i<y;i++)	if(abs(m[p][kx])<abs(m[i][kx]))	p=i;
				if(p!=ky)	swap(m[p],m[ky]);
			//	cout<<kx<<" "<<ky<<endl;
				if(abs(m[ky][kx])<1e-10)
				{	ky--;	continue;		}	
				
				long double t=m[ky][kx];
				for(int i=0;i<x;i++)	m[ky][i]/=t; 
				for(int i=0;i<y;i++)	if(i!=ky)
				{
					long double t=m[i][kx];
					for(int j=0;j<x;j++)	m[i][j]-=t*m[ky][j];
				}
			}
			//debug();
			for(int i=0;i<y;i++)	ans[i]=m[i][x-1];
		}
}ma;
class Graph
{
	public:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*100*2];
		int pre[maxn],en;
		Graph()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
}b,a;
class Tarjan
{
	private:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*100*2];
		int pre[maxn],en;
		int vis[maxn],low[maxn],tn,ist[maxn];
		stack <int> sta; 
		void tarjan(int u)
		{
			vis[u]=low[u]=++tn;
			ist[u]=1;	sta.push(u);
			for(int i=b.pre[u];i!=-1;i=b.e[i].nxt)
			{
				int v=b.e[i].v;
				if(vis[v]==0)	tarjan(v),low[u]=min(low[u],low[v]);
				else	if(ist[v])	low[u]=min(low[u],vis[v]);
			}
		//	cout<<vis[u]<<" "<<low[u]<<endl;
			if(low[u]==vis[u])
			{
				bn++;
				int t;
				do
				{
					t=sta.top();	sta.pop();	ist[t]=0;
					blo[t]=bn;
					lis[bn].push_back(t);
					idx[t]=lis[bn].size()-1;
				}while(t!=u);
			}
		}
	public:
		int n;
		int blo[maxn],bn;
		int idx[maxn];
		vector <int> lis[maxn];
		void build()
		{
			for(int i=1;i<=n;i++)	if(vis[i]==0)	tarjan(i);
		//	for(int i=1;i<=n;i++)	cout<<i<<"~"<<blo[i]<<"~"<<idx[i]<<endl;
			for(int u=1;u<=n;u++)
				for(int i=b.pre[u];i!=-1;i=b.e[i].nxt)
				{
					int v=b.e[i].v;
					if(blo[u]!=blo[v])	a.addedge(blo[u],blo[v]);
				}
		}
}tj;
int tpo[maxn],tn;
int vis[maxn];
void dfs(int u)
{
	vis[u]=1;
	for(int i=a.pre[u];i!=-1;i=a.e[i].nxt)
	{
		int v=a.e[i].v;
		if(vis[v]==0)	dfs(v);
	}
	tpo[++tn]=u;
}
int n,m,s,t;
long double dyp[maxn];
void work()
{
	dfs(tj.blo[s]);
	for(int i=1;i<=n;i++)	dyp[i]=1e3000;
	dyp[t]=0;
	for(int k=1;k<=tn;k++)
	{
		int p=tpo[k];
	//	cout<<tj.lis[p].size()<<endl;
		ma.init(tj.lis[p].size(),tj.lis[p].size()+1);
		for(int i=0;i<tj.lis[p].size();i++)
		{
			int u=tj.lis[p][i];	int cnt=0;
			if(u==t)	ma.m[tj.idx[u]][tj.idx[u]]=1; 
			else
			{
				for(int i=b.pre[u];i!=-1;i=b.e[i].nxt)
				{
					int v=b.e[i].v;	cnt++;
					if(tj.blo[u]==tj.blo[v])	ma.m[tj.idx[u]][tj.idx[v]]--;
					else	ma.m[tj.idx[u]][tj.lis[p].size()]+=dyp[v];
				}
				if(cnt==0)	ma.m[tj.idx[u]][tj.lis[p].size()]=1e3000;
				ma.m[tj.idx[u]][tj.idx[u]]+=cnt;
				ma.m[tj.idx[u]][tj.lis[p].size()]+=cnt;
			}
		//	cout<<cnt<<endl;
		}
		//ma.debug();
		ma.guass();
		for(int i=0;i<tj.lis[p].size();i++)
		{
			int u=tj.lis[p][i];
			if(dyp[u]>=1e3000)	dyp[u]=ma.ans[tj.idx[u]];
		}
	}
}
int main()
{
//	freopen("labyrinth10.in","r",stdin); 
	scanf("%d%d%d%d",&n,&m,&s,&t);
	tj.n=n;
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		b.addedge(u,v);
	}
	tj.build();
	work();
	if(dyp[s]!=dyp[s]||dyp[s]>=1e3000||vis[tj.blo[t]]==0)	printf("INF\n");
	else	printf("%.3lf\n",(double)dyp[s]);
}
