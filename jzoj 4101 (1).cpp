#include<algorithm>
//#include<iostream>
#include<cstring> 
#include<cstdio>
using namespace std;
const int maxn=100100;
int n,m;
class Edge
{
	public:
		int u,v,c;
		bool operator <(const Edge &in)const
		{
			return c<in.c;
		}
}e[maxn];
class Query
{
	public:
		int u,x,p;
		bool operator <(const Query &in)const
		{
			return x<in.x;
		}
}q[maxn];
class Tree
{
	private:
		class Edge
		{
			public:
				int v;
				int nxt;
		}e[maxn*2];
		int pre[maxn],en=0;
		int lev[maxn]; 
		int bfa[maxn],bsz[maxn],bdi[maxn][2];
		int ups[maxn][20];
		void dfsmer(int u,int f,int ff)
		{
			bfa[u]=ff;	lev[u]=lev[f]+1;
			ups[u][0]=f;
			for(int i=1;i<20;i++)	ups[u][i]=ups[ups[u][i-1]][i-1];
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)	dfsmer(v,u,ff);
			}
		}
		int getdis(int ui,int vi)
		{
			int u=ui,v=vi;
			if(lev[v]<lev[u])	swap(v,u);
			int t=lev[v]-lev[u]; 
			for(int i=0;i<20;i++)	if((t&(1<<i))==(1<<i))	v=ups[v][i];
			if(u!=v)
			{
				for(int i=19;i>=0;i--)	if(ups[u][i]!=ups[v][i])	u=ups[u][i],v=ups[v][i];
				for(int i=0;i<20;i++)
					if(ups[u][i]==ups[v][i])
					{
						u=ups[u][i],v=ups[v][i];
						break;
					}
			}
			//cout<<ui<<"="<<vi<<"="<<u<<" "<<lev[ui]<<"="<<lev[vi]<<"="<<2*lev[u]<<endl;
			return lev[ui]+lev[vi]-2*lev[u];
		}
	public:
		void init()
		{
			memset(pre,-1,sizeof pre);	en=0;
			for(int i=1;i<=n;i++)
			{
				for(int j=0;j<20;j++)	ups[i][j]=i;
				bfa[i]=i;
				bsz[i]=1;
				bdi[i][0]=bdi[i][1]=i;
				lev[i]=1;
			}
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++; 
		}
		void merge(int u,int v)
		{
			int uf=bfa[u],vf=bfa[v];
			addedge(u,v);
			if(bsz[vf]>bsz[uf])	swap(u,v),swap(uf,vf);
			bsz[uf]+=bsz[vf];
			
			dfsmer(v,u,uf);
			int mxa=-1,di0=0,di1=0;
			if(getdis(bdi[uf][0],bdi[uf][1])>mxa)	mxa=getdis(bdi[uf][0],bdi[uf][1]),di0=bdi[uf][0],di1=bdi[uf][1];
			if(getdis(bdi[vf][0],bdi[vf][1])>mxa)	mxa=getdis(bdi[vf][0],bdi[vf][1]),di0=bdi[vf][0],di1=bdi[vf][1];
			for(int i=0;i<=1;i++)
				for(int j=0;j<=1;j++)
					if(getdis(bdi[uf][i],bdi[vf][j])>mxa)	mxa=getdis(bdi[uf][i],bdi[vf][j]),di0=bdi[uf][i],di1=bdi[vf][j];
			bdi[uf][0]=di0;
			bdi[uf][1]=di1;
		}
		int query(int u)
		{
			//cout<<u<<" "<<bdi[bfa[u]][0]<<" "<<getdis(u,bdi[bfa[u]][0])<<endl;
			//cout<<u<<" "<<bdi[bfa[u]][1]<<" "<<getdis(u,bdi[bfa[u]][1])<<endl;
			//cout<<u<<" "<<bfa[u]<<" "<<bdi[bfa[u]][0]<<"="<<bdi[bfa[u]][1]<<endl; 
			return max(getdis(u,bdi[bfa[u]][0]),getdis(u,bdi[bfa[u]][1]));
		}
		/*
		void debug()
		{
			for(int i=1;i<=n;i++)
			{
				cout<<i<<"="<<lev[i]<<endl;
				for(int j=0;j<20;j++)	cout<<ups[i][j]<<" ";
				cout<<endl;
			}
			cout<<"==="<<endl;
			cout<<getdis(1,2)<<"==="<<endl;
			cout<<"==="<<endl;
		}
		*/
}tr;
int ans[maxn];
int main()
{
	freopen("travel1.in","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)	scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)	scanf("%d%d",&q[i].u,&q[i].x),q[i].p=i; 
	sort(e+1,e+n);
	sort(q+1,q+m+1);
//	for(int i=1;i<=m;i++)	cout<<q[i].u<<" "<<q[i].x<<endl;
	tr.init();
	int p=1;
	for(int i=1;i<=n-1;i++)
	{
		for(;p<=m&&q[p].x<e[i].c;p++)	ans[q[p].p]=tr.query(q[p].u)+1;
		tr.merge(e[i].u,e[i].v);
	}
	for(;p<=m;p++)	ans[q[p].p]=tr.query(q[p].u)+1;
//	tr.debug();
	for(int i=1;i<=m;i++)	printf("%d\n",ans[i]);
	
}
