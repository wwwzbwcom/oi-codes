#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=500;
const int oo=1e8;
class Dinic
{
	private:
		class Edge
		{
			public:
				int v,c;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int lev[maxn];
		bool bfs()
		{
			queue <int> que;	memset(lev,-1,sizeof lev);
			que.push(sta);	lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(lev[v]==-1&&c)
					{
						lev[v]=lev[u]+1;
						if(v==end)	return 1;
						que.push(v);
					}
				}
			}
			return 0;
		}
		int dfs(int u,int lc)
		{
			//cout<<u<<endl;
			if(u==end)	return lc;
			int nc=0;
			for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==lev[u]+1&&c)
				{
					int cc=min(c,lc-nc);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			if(nc==0)	lev[u]=-1;
		//	else	cout<<u<<endl;
			return nc;
		}
	public:
		int sta,end,n;
		void init()
		{
			memset(pre,-1,sizeof pre);
			sta=end=n=en=0;
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		int dinic()
		{
			int ans=0;
			while(bfs())
			{
			//	cout<<"===================================="<<endl;
				int tmp=dfs(sta,oo);
			//	cout<<tmp<<"==============================="<<endl;
				ans+=tmp;
			}
			return ans;
		}
	
}dnc;
int main()
{
	int h,w,c,m,nw,nc,nm;
	while(cin>>h>>w>>c>>m>>nw>>nc>>nm)
	{
		if(h==-1)	return 0;
		dnc.init();
		dnc.n=(h+w+c+m)*2+8;
		dnc.sta=(h+w+c+m)*2+1;	dnc.end=(h+w+c+m)*2+8;
		for(int i=1;i<=h;i++)	dnc.addedge((h+w+c+m)*2+1,i*2-1,1),dnc.addedge(i*2-1,i*2,1),dnc.addedge(i*2,(h+w+c+m)*2+2,1);
		for(int i=1;i<=w;i++)	dnc.addedge((h+w+c+m)*2+3,(h+i)*2-1,1),dnc.addedge((h+i)*2-1,(h+i)*2,1),dnc.addedge((h+i)*2,(h+w+c+m)*2+4,1);
		for(int i=1;i<=c;i++)	dnc.addedge((h+w+c+m)*2+5,(h+w+i)*2-1,1),dnc.addedge((h+w+i)*2-1,(h+w+i)*2,1),dnc.addedge((h+w+i)*2,(h+w+c+m)*2+6,1);
		for(int i=1;i<=m;i++)	dnc.addedge((h+w+c+m)*2+7,(h+w+c+i)*2-1,1),dnc.addedge((h+w+c+i)*2-1,(h+w+c+i)*2,1),dnc.addedge((h+w+c+i)*2,(h+w+c+m)*2+8,1);
		
		dnc.addedge((h+w+c+m)*2+2,(h+w+c+m)*2+5,nw);
		dnc.addedge((h+w+c+m)*2+4,(h+w+c+m)*2+7,nc);
		dnc.addedge((h+w+c+m)*2+6,(h+w+c+m)*2+8,nm);
		
		for(int i=1;i<=w;i++)
		{
			int ni;	cin>>ni;
			for(int j=1;j<=ni;j++)
			{
				int u;	cin>>u;
				dnc.addedge(u*2,(h+i)*2-1,1);
			}
		}
		for(int i=1;i<=c;i++)
		{
			int ni;	cin>>ni;
			for(int j=1;j<=ni;j++)
			{
				int u;	cin>>u;
				dnc.addedge((h+u)*2,(h+w+i)*2-1,1);
			}
		}
		for(int i=1;i<=m;i++)
		{
			int ni;	cin>>ni;
			for(int j=1;j<=ni;j++)
			{
				int u;	cin>>u;
				dnc.addedge((h+w+u)*2,(h+w+c+i)*2-1,1);
			}
		}
		cout<<dnc.dinic()<<endl;
	}
}
