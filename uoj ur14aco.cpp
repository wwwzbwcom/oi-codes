#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<map>
using namespace std;
const int maxn=100100;
int n;
bool boo[maxn];
int pri[maxn],pn;
map <int,bool> isp;
map <int,long long>	idx;
void init()
{
	boo[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
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
				int v,nxt;
				long long c;
		}e[maxn*2];
		int pre[maxn],en;
		long long dis[maxn];
		void dfs(int u,int f,long long con)
		{
			dis[u]=con;
		//	cout<<u<<"="<<con<<endl;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;	long long c=e[i].c;
				if(v!=f)	dfs(v,u,con^c);
			}
		} 
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v,long long c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		long long work()
		{
			dfs(1,-1,0);
			sort(dis+1,dis+n+1);
			
			dis[n+1]=2e18;
		//	for(int i=1;i<=n+1;i++)	cout<<i<<" "<<dis[i]<<endl;
		//	cout<<endl; 
			long long ans=0;
			for(int i=1;i<=n;)
			{
				int end=upper_bound(dis+1,dis+n+1,dis[i])-dis-1;
				ans+=(long long)(end-i+1)*(end-i);
				i=end+1;
			}
			return	ans;
		}
}tr;
long long randll()
{
	long long ans=1;
	for(int i=1;i<=4;i++)	ans*=(rand()+1ll);
	return ans;
}
int main()
{
	srand(time(0));
	init();
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v,tmp;	scanf("%d%d%d",&u,&v,&tmp);
		long long c=0;
		//cout<<i<<"================="<<endl;
		int flag=0;
		if(isp.find(tmp)==isp.end())
		{
			for(int j=1;pri[j]<=tmp&&j<=pn;j++)
			{
				int cnt=0;
				while(tmp%pri[j]==0)	cnt++,tmp/=pri[j],flag=1;
				if(cnt%2==1)
				{
					if(idx.find(pri[j])==idx.end())	idx[pri[j]]=randll();
					c^=idx[pri[j]];	//cout<<pri[j]<<" "<<idx[pri[j]]<<endl;
				}
			}
			if(flag==0)	isp[tmp]=1;
		}
		if(tmp!=1)
		{
			if(idx.find(tmp)==idx.end())	idx[tmp]=randll();
			c^=idx[tmp];
		//	cout<<tmp<<"="<<idx[tmp]<<endl;
		}
		//cout<<u<<" "<<v<<" "<<"="<<c<<endl;
		tr.addedge(u,v,c);
	}
	printf("%lld",tr.work());
}
