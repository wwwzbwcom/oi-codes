#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=200;
int n,m;
class Graph
{
	private: 
		class Edge
		{
			public:
				int v;
				string c;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int ans[maxn];
		void dfs(int u,string a,string b)
		{
			if(a==b)	ans[a.size()-1]++;
			if(a.size()>=2*n+1)	return;
			if(b.size()>=2*n+1)	return;
			int lim=min(a.size(),b.size());
			if(a.substr(0,lim)!=b.substr(0,lim))	return;
			
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;	string c=e[i].c;
				dfs(v,a+(char)v,b+c);
			}
		}
	public:
		Graph()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,string c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		}
		void work()
		{
			string tmp="";
			for(int i=1;i<=n;i++)	dfs(i,tmp+(char)(i),"");
			for(int i=1;i<=n*2;i++)	cout<<ans[i]<<endl;
		}
}gp;
int main()
{
	freopen("vision.in","r",stdin);
	freopen("vision.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,k;	string c;
		cin>>u>>v>>k;
		for(int i=0;i<k;i++)
		{
			int t;	cin>>t;
			c+=t; 
		} 
		gp.addedge(u,v,c);
	}
	gp.work();
}
