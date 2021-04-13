#include<iostream>
using namespace std;
const int maxn=100000;
class Tree
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int dyp[maxn][2];
		void dfs(int u,int f)
		{
			int flag=-1,mxa=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)
				{
					dfs(v,u)
					mxa=max(mxa,dyp[v][0]);
					if(flag==-1)	flag=dyp[v][0];
					else	if(flag!=dyp[v][0])	flag=-2;
				}
			}
			if(flag==-1)	dyp[u][0]=0,dyp[u][1]=1;
			else
			{
				if(flag==-2)	dyp[u][0]=mxa;
				else	dyp[u][0]=mxa+1;
				int ans=1;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					if(v!=f)
					{
						if(flag==-2)
						{
							if(dyp[v][0]<mxa)	ans=((long long)ans*dyp[v][1])%q;
						}
						else	ans=((long long)ans*dyp[v][1])%q;
					}
				}
				dyp[u][1]=ans;
			}
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void work()
		{
			dfs(1,-1);
			cout<<dyp[1][0]<<endl;
			cout<<dyp[1][1]; 
		}
}
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		tr.addedge(u,v); 
	}
	tr.work();
}
