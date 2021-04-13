#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
const int maxn=100100;
class Graph
{
	public:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int n;
		Graph()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
};
class Tarjan
{
	private:
		int vis[maxn],low[maxn],cnt;
		
		stack <int> sta;
		void tarjan(int u)
		{
			vis[u]=low[u]=++cnt;	ist[u]=1; sta.push(u);
		//	cout<<u<<"=1="<<vis[u]<<"="<<low[u]<<endl;
			for(int i=in.pre[u];i!=-1;i=in.e[i].nxt)
			{
				int v=in.e[i].v;
			//	cout<<u<<"="<<v<<endl;
				if(!vis[v])	tarjan(v),low[u]=min(low[u],low[v]);
				else	if(ist[v])	low[u]=min(low[u],vis[v]);
			}
		//	cout<<u<<"="<<vis[u]<<"="<<low[u]<<endl;
			if(vis[u]==low[u])
			{
				int tmp;
				bn++;
				do
				{
					tmp=sta.top();	sta.pop();	ist[tmp]=0;
					blo[tmp]=bn;
				}while(tmp!=u);
			}
		}
	public:
		int ist[maxn],blo[maxn],bn;
		Graph in,out;
		void gettar()
		{
			for(int i=1;i<=in.n;i++)	if(!vis[i])	tarjan(i);
		//	for(int i=1;i<=in.n;i++)	cout<<i<<"="<<blo[i]<<endl;
			for(int u=1;u<=in.n;u++)
			{
				for(int i=in.pre[u];i!=-1;i=in.e[i].nxt)
				{
					int v=in.e[i].v;
					if(blo[u]!=blo[v])	out.addedge(blo[u],blo[v]);//,cout<<blo[u]<<"="<<blo[v]<<endl;
				}
			}
			out.n=bn;
		}
}trj;
class Topo
{
	public:
		Graph gph;
		int vis[maxn];
		void topo(int u)
		{
			vis[u]=1;
		//	cout<<u<<"="<<gph.n<<endl;
			for(int i=gph.pre[u];i!=-1;i=gph.e[i].nxt)
			{
				int v=gph.e[i].v;
				if(vis[u]==0)	topo(v);
			}
			lis[++ln]=u;
		}
		int lis[maxn],ln;
		gettop()
		{
			for(int i=1;i<=gph.n;i++)	if(vis[i]==0)	topo(i);
		}
}tpo;
int n,m,s,f;
int sta[maxn],fin[maxn];
double dyp[maxn];
Graph g;
double work()
{
	memset(dyp,0,sizeof dyp);
	for(int i=1;i<=g.n;i++)	if(sta[i])	dyp[trj.blo[i]]=1;
	for(int k=tpo.ln;k>=1;k--)
	{
		int u=tpo.lis[k];
	//	cout<<u<<endl;
		int cnt=0;
		for(int i=g.pre[u];i!=-1;i=g.e[i].nxt)	cnt++;
		if(cnt==0)	continue;
		for(int i=g.pre[u];i!=-1;i=g.e[i].nxt)
		{
			int v=g.e[i].v;
			dyp[v]+=dyp[u]/(double)cnt;
		//	cout<<u<<"~"<<v<<" "<<dyp[v]<<" "<<dyp[u]<<" "<<cnt<<endl;
		}
	}
	double ans=1;
	for(int i=1;i<=g.n;i++)	if(fin[i])	ans*=(1-dyp[trj.blo[i]]);
	double tmp=ans;
	ans*=tmp;	ans*=tmp;
	return 1-ans;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&f);
	trj.in.n=n;
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		trj.in.addedge(u,v);
	}
	int v;
	for(int i=1;i<=s;i++)	scanf("%d",&v),sta[v]=1;
	for(int i=1;i<=f;i++)	scanf("%d",&v),fin[v]=1;
	trj.gettar();
	tpo.gph=trj.out;
	g=trj.out;
	tpo.gettop();
	printf("%.10lf",work());
}
