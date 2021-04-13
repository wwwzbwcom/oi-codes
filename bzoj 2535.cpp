#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
#include<list>
using namespace std;
const int maxn=2010;
int n,m;
int kva[maxn];
class Graph
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn*10];
		int pre[maxn],en;
		int deg[maxn];
		stack <int> sta;
		class Con
		{
			public:
				Con(int ui,int ki)
				{
					u=ui;	k=ki;
				}
				int u,k;
				bool operator <(const Con &in)const
				{
					return k>in.k;
				}
		};
		priority_queue <Con> que; 
	public:
		Graph()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		int work(int mod)
		{
			memset(deg,0,sizeof deg);
			while(!que.empty())	que.pop();
			for(int i=0;i<en;i++)	deg[e[i].v]++;
			for(int i=1;i<=n;i++)	if(i!=mod&&deg[i]==0)	que.push(Con(i,kva[i]));
			for(int p=1;p<=n;p++)
			{
				if(que.empty())	return p;
				Con cur=que.top();	que.pop();
				int u=cur.u,k=cur.k;
				sta.push(u);
				if(k>p)	return p;
				
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					deg[v]--;
					if(v!=mod&&deg[v]==0)	que.push(Con(v,kva[v]));
				}
			}
			int cnt=0;
			while(!sta.empty())	printf("%d ",sta.top()),sta.pop(),cnt++;
			printf("\n");
			return 0;
		}
}gp;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&kva[i]),kva[i]=n-kva[i]+1;
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(v,u);
	}
	gp.work(0);
//	return 0;
	for(int i=1;i<=n;i++)	printf("%d ",n-gp.work(i)+1);
}
