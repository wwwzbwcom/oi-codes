#include<iostream>
#include<cstring>
#include<set>
using namespace std;
const int maxn=3010;
int n;
int boo[10010];
int pri[10010],pn;
void init()
{
	boo[1]=1;
	for(int i=2;i<10010;i++)
	{
		if(boo[i]==0)	pri[pn++]=i;
		for(int j=0;j<pn;j++)
		{
			if(i*pri[j]>=10010)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
class Tree
{
	private:
		class Edge
		{
			public:
				int v;
				int c[50],cn;
				int nxt;
		}e[maxn*2];
		int pre[maxn],en;
		bool cur[(int)1e8+10];
		int curn;
		inline void merge(int p)
		{
			for(int i=0;i<e[p].cn;i++)
			{
				int u=e[p].c[i];
				if(cur[u])	cur[u]=false,curn--;
				else	cur[u]=true,curn++;
			}
		}
		int dfs(int u,int f)
		{
			int ans=0;
			if(f!=-1&&curn==0)	ans=1;	else	ans=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				if(e[i].v!=f)
				{
					merge(i);
					ans+=dfs(e[i].v,u);
					merge(i);
				}
			}
			return ans;
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			int t[50],tn=0;
			memset(t,0,sizeof t);
			for(int i=0;i<pn;i++)
			{
				int cnt=0;
				while(c%pri[i]==0)	cnt++,c/=pri[i];
				if(cnt%2)	t[tn++]=pri[i];
			}
			if(c!=1)	t[tn++]=c;
			e[en].v=v;	memcpy(e[en].c,t,sizeof(int)*50);	e[en].cn=tn;	e[en].nxt=pre[u];	pre[u]=en++;
			e[en].v=u;	memcpy(e[en].c,t,sizeof(int)*50);	e[en].cn=tn;	e[en].nxt=pre[v];	pre[v]=en++;
		}
		int work()
		{
			int ans=0;
			for(int i=1;i<=n;i++)	ans+=dfs(i,-1);
			return ans;
		}
}tr;
int main()
{
//	freopen("in.txt","r",stdin);
	init();
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		tr.addedge(u,v,c);
	}
	return 0;
	cout<<tr.work()<<endl;
}
