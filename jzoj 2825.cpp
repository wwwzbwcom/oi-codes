#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1100;
class Tree
{
	private:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		class Lis
		{
			public:
				int s[maxn];
				int n,p;
				void init()
				{
					n=p=0; 
				}
				bool operator <(const Lis &in)const
				{
					return (n-p)<(in.n-in.p);
				}
		}lis[maxn];
		priority_queue <Lis> que;
		int ln;
		class Ans
		{
			public:
				int s[maxn][2];
				int n;
				void init()
				{
					n=0;
				}
				bool operator <(const Ans &in)const
				{
					return	n<in.n;
				}
		}ans,tmp;
		void dfsans(int u,int f,int ff)
		{
			int flag=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)
				{
					if(ff==-1)	dfsans(v,u,ln++);
					else	dfsans(v,u,ff);
					flag=0;
				} 
			}
			if(flag==1)	lis[ff].s[lis[ff].n++]=u;
		}
	public:
		int idx[maxn];
		int n;
		void init()
		{
			memset(pre,-1,sizeof pre);	en=0;
			
			memset(idx,0,sizeof idx);
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void getans()
		{
			ans.init();
			ans.n=1e9;
			for(int i=1;i<=n;i++)
			{
				ln=0;
				for(int j=0;j<maxn;j++)	lis[j].init();
				tmp.init();
				
				dfsans(i,-1,-1);
				for(int i=0;i<ln;i++)	que.push(lis[i]);
				while(!que.empty())
				{
					Lis q1,q2;
					int flag=1;
					if(!que.empty())	q1=que.top(),que.pop();
					if(!que.empty())	q2=que.top(),que.pop(),flag=0;
					if(flag)
					{
						tmp.s[tmp.n][0]=q1.s[q1.p++];
						tmp.s[tmp.n][1]=i;
						tmp.n++;
						if(q1.p<q1.n)	que.push(q1);
					}
					else
					{
						tmp.s[tmp.n][0]=q1.s[q1.p++];
						tmp.s[tmp.n][1]=q2.s[q2.p++];
						tmp.n++;
						if(q1.p<q1.n)	que.push(q1);
						if(q2.p<q2.n)	que.push(q2);	
					}
				}
				while(!que.empty())	que.pop();
				if(tmp<ans)	ans=tmp;
			}
			cout<<ans.n<<endl;
			for(int i=0;i<ans.n;i++)	cout<<idx[ans.s[i][0]]<<" "<<idx[ans.s[i][1]]<<endl;	
		}
}tr;
class Tarjan
{
	private:
		class Edge
		{
			public:
				int u,v,m,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int vis[maxn],low[maxn],tn;
		int bfa[maxn],bn;
		void dfstar(int u,int fe)
		{
			vis[u]=low[u]=++tn;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(i/2!=fe/2)
				{
					if(vis[v]==0)	dfstar(v,i),low[u]=min(low[u],low[v]);
					else	low[u]=min(low[u],vis[v]);
				}
			}
			if(fe>=0&&vis[u]==low[u])	e[fe].m=e[fe^1].m=1;
		}
		void dfsblo(int u)
		{
			vis[u]=1;	bfa[u]=bn;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,m=e[i].m;
				if(vis[v]==0&&m==0)	dfsblo(v);
			}
		}
	public:
		int n;
		void init()
		{
			memset(pre,-1,sizeof pre);	en=0;
			
			memset(vis,0,sizeof vis);
			memset(low,0,sizeof low);	tn=0;
			
			memset(bfa,0,sizeof bfa);	bn=0;
		}
		void addedge(int u,int v)
		{
			e[en].u=u;e[en].v=v;e[en].m=0;e[en].nxt=pre[u];pre[u]=en++;
			e[en].u=v;e[en].v=u;e[en].m=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		void gettar()
		{
			dfstar(1,-10);
			memset(vis,0,sizeof vis);
			for(int i=1;i<=n;i++)	if(vis[i]==0)	bn++,tr.idx[bn]=i,dfsblo(i);
			tr.n=bn;
			for(int i=0;i<en;i+=2)
			{
				int u=e[i].u,v=e[i].v;
				if(bfa[u]!=bfa[v])	tr.addedge(bfa[u],bfa[v]);
			}
		}
}ta;
int n,m;
int main()
{
	cin>>n>>m;
	ta.n=n;
	ta.init();
	tr.init();
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		ta.addedge(u,v);
	}
	ta.gettar();
	tr.getans();
}
