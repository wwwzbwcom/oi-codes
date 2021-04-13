#include<iostream>
#include<cstring>
#include<set>
using namespace std;
const int maxn=205;
const int oo=1e9;
set <long long> boo;
int n,m;
class Dinic
{
	private:
		class Edge
		{
			public:
				short v,nxt;
				int c;
		}e[maxn*10*2];
		short pre[maxn],en;
		short que[maxn],qsn,qen;
		short lev[maxn];
		short sta,end;
		bool bfs()
		{
			qsn=qen=0;	memset(lev,0,sizeof lev);
			que[qen++]=sta;	lev[sta]=1;
			while(qsn<qen)
			{
				short u=que[qsn];	qsn++;
			//	cout<<u<<endl;
				for(short i=pre[u];i!=-1;i=e[i].nxt)
				{
					short v=e[i].v;	int	c=e[i].c;
					if(lev[v]==0&&c)
					{
						lev[v]=lev[u]+1;
						if(v==end)	return true;
						que[qen++]=v;
					}
				}
			}
			return false;
		}
		int dfs(short u,int lc)
		{
			if(u==end)	return lc;
			int nc=0;
			for(short i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
			{
				short v=e[i].v;	int	c=e[i].c;
				if(lev[u]+1==lev[v]&&c)
				{
					short cc=min(c,lc-nc);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			if(nc)	lev[u]=-1;
			return nc;
		}
	public:
		Dinic()
		{
			memset(pre,-1,sizeof pre);
		}
		void copy(Dinic &in)const
		{
			
			memcpy(in.e,e,sizeof e);
			memcpy(in.pre,pre,sizeof pre);
			//for(int i=0;i<en;i++)	cout<<pre[i]<<" "<<in.pre[i]<<endl;
			in.en=en;
		}
		inline void addedge(int u,int v,int c)
		{
			e[en].v=v;	e[en].c=c;	e[en].nxt=pre[u];	pre[u]=en++;
			e[en].v=u;	e[en].c=c;	e[en].nxt=pre[v];	pre[v]=en++;
		}
		inline long long work(int stai,int endi)
		{
			sta=stai;	end=endi;
			long long ans=0;
			while(bfs())
			{
				int t;
				do
				{
					t=dfs(sta,oo);
					ans+=t;
				}while(t);
			}
			return ans;
		}
}ba,di;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		ba.addedge(u,v,c);
	}
	for(int i=1;i<=n;i++)
	{
		
		for(int j=i+1;j<=n;j++)
		{
			ba.copy(di);
			boo.insert(di.work(i,j));
		}
	}
	cout<<boo.size()<<endl;
}
