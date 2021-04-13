#include<iostream>
#include<cstring>
using namespace std;
const int maxn=300100;
int n,m,q;
int val[maxn];
int lasx,lasy,lask;
int lasans;
class Tree
{
	private:
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int lev[maxn],fat[maxn];
		void dfsbui(int u,int f,int l)
		{
			lev[u]=l;	fat[u]=f;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)	dfsbui(v,u,l+1);
			}
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{
			dfsbui(1,-1,1); 
		}
		void query(int u,int v,int k)
		{
			lasx=lasy=lask=0;
			if(lev[v]>lev[u])	swap(u,v);
			while(lev[u]>lev[v])
			{
				if(val[u]<k)	lasx++;
				if(val[u]==k)	lasy++;
				if(val[u]>k)	lask++;
				u=fat[u];
			}
			while(u!=v)
			{
				if(val[u]<k)	lasx++;
				if(val[u]==k)	lasy++;
				if(val[u]>k)	lask++;
				u=fat[u];
				if(val[v]<k)	lasx++;
				if(val[v]==k)	lasy++;
				if(val[v]>k)	lask++;
				v=fat[v];
			}
			if(val[u]<k)	lasx++;
			if(val[u]==k)	lasy++;
			if(val[u]>k)	lask++;
			cout<<lasx<<" "<<lasy<<" "<<lask<<endl;
		}
}tr;
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)	cin>>val[i];
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	cin>>u>>v;
		tr.addedge(u,v);
	}
	tr.build();
	for(int i=1;i<=q;i++)
	{
		int x,y,k;	cin>>x>>y>>k; 
		lasans=(lasx^lasy^lask);
		x^=lasans;	y^=lasans; k^=lasans;
		tr.query(x,y,k);
	}
}
