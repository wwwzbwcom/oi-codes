#include<iostream>
#include<cstring>
#include<string> 
#include<stack>
#include<map>
using namespace std;
const int maxn=110;
class Tarjan
{
	private: 
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn],low[maxn],tn;
		int ins[maxn];
		stack <int> sta;
		int bfa[maxn],bsz[maxn],bn;
		int edg[maxn][maxn],dis[maxn][maxn],boo[maxn][maxn];
		void dfstrj(int u,int fe)
		{
			vis[u]=low[u]=++tn;	ins[u]=1;	sta.push(u);
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(i!=fe)
				{
					if(vis[v]==0)	dfstrj(v,i),low[u]=min(low[u],low[v]);
					else	if(ins[v])	low[u]=min(low[u],vis[v]);
				}
			}
			if(low[u]==vis[u])
			{
				int t;
				bn++;
				do
				{
					t=sta.top();	sta.pop();	ins[t]=0;
					bfa[t]=bn;	bsz[bn]++;
				}while(t!=u);
			}
		} 
	public:
		int n;
		int ans;
		void init()
		{
			n=0;
			 
			memset(pre,-1,sizeof pre);	en=0;
			
			memset(vis,0,sizeof vis);
			memset(low,0,sizeof low);	tn=0;
			memset(ins,0,sizeof ins);	
			
			memset(bfa,0,sizeof bfa);
			memset(bsz,0,sizeof bsz);	bn=0;
			
			memset(edg,0,sizeof edg);
			memset(dis,0,sizeof dis);
			memset(boo,0,sizeof boo);
			
			ans=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		void tarjan()
		{
			for(int i=1;i<=n;i++)	if(vis[i]==0)	dfstrj(i,-1);
			for(int u=1;u<=n;u++)
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					edg[bfa[u]][bfa[v]]=dis[bfa[u]][bfa[v]]=1;
				}
			for(int i=1;i<=bn;i++)	edg[i][i]=dis[i][i]=1;
		}
		void work()
		{
			for(int k=1;k<=bn;k++)
				for(int i=1;i<=bn;i++)
					for(int j=1;j<=bn;j++)
						if(dis[i][k]&&dis[k][j])
							dis[i][j]=1;
							
			for(int i=1;i<=bn;i++)	if(bsz[i]>1)	ans+=bsz[i];
		//	for(int i=1;i<=n;i++)	cout<<i<<"~"<<bfa[i]<<endl;
		//	cout<<bn<<endl;
			
			for(int u=1;u<=n;u++)
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					if(bfa[u]!=bfa[v])
					{
						int flag=1;
						//cout<<bfa[u]<<" "<<bfa[v]<<" "<<boo[bfa[u]][bfa[v]]<<endl;
						for(int k=1;k<=bn;k++)	if(k!=bfa[v]&&k!=bfa[u]&&edg[bfa[u]][k]&&dis[k][bfa[v]])	flag=0;//cout<<dis[k][bfa[v]]<<endl;
						if(boo[bfa[u]][bfa[v]]==0)	ans+=flag,boo[bfa[u]][bfa[v]]=1;//cout<<bfa[u]<<"="<<bfa[v]<<" "<<flag<<endl;
					}
				}
		}
}tr;
string nam[maxn];

map <string,int> idx; 
string edg[maxn][maxn];
int edn[maxn];
int main()
{
	freopen("out.txt","w",stdout);
	int gn;	cin>>gn;
	while(gn--)
	{
		int n;	cin>>n;
		idx.clear();
		for(int i=1;i<=n;i++)
		{
			cin>>nam[i];	idx[nam[i]]=i;
			cin>>edn[i];
			for(int j=1;j<=edn[i];j++)	cin>>edg[i][j];
		}
		tr.init();
		tr.n=n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=edn[i];j++)
			//	cout<<idx[nam[i]]<<"="<<idx[edg[i][j]]<<endl,
				tr.addedge(idx[nam[i]],idx[edg[i][j]]);
		tr.tarjan();
		tr.work();
		cout<<tr.ans<<endl;
	}
}
