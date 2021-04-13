#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100100;
int x2t[maxn],t2x[maxn],xn;
int n,q;
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int sum,set;
		}n[maxn*3];
		int nn;
		void push(int u)
		{
			if(n[u].set!=-1)
			{
				if(n[u].ls!=0)
				{
					n[n[u].ls].set=n[u].set;
					n[n[u].rs].set=n[u].set;
				}
				n[u].sum=n[u].set*(n[u].re-n[u].le+1);
				n[u].set=-1;
			}
		}
		void pull(int u)
		{
			n[u].sum=0;
			if(n[n[u].ls].set==-1)	n[u].sum+=n[n[u].ls].sum;
			else	n[u].sum+=n[n[u].ls].set*(n[n[u].ls].re-n[n[u].ls].le+1);
			
			if(n[n[u].rs].set==-1)	n[u].sum+=n[n[u].rs].sum;
			else	n[u].sum+=n[n[u].rs].set*(n[n[u].rs].re-n[n[u].rs].le+1);
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			n[u].set=-1;
			if(le==re)	n[u].sum=1;
			else
			{
				int mid=(le+re)>>1;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			}
			return u;
		}
		int qrysum(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			
		//	getchar(); 
			if(le==lc&&re==rc)
			{
			//	cout<<le<<"="<<re<<" "<<n[n[u].ls].sum<<"="<<n[n[u].rs].sum<<" "<<n[u].sum<<" "<<n[u].set<<endl;
				if(n[u].set==-1)	return n[u].sum;
				else	return n[u].set*(re-le+1);
			}
			else
			{
				push(u);
				if(rc<=mid)	return qrysum(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrysum(n[u].rs,lc,rc);
					else	return qrysum(n[u].ls,lc,mid)+qrysum(n[u].rs,mid+1,rc);
				}
				pull(u);
			}
		}
		void optrng(int u,int lc,int rc,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			if(le==lc&&re==rc)	n[u].set=val;
			else
			{
				push(u);
				if(rc<=mid)	optrng(n[u].ls,lc,rc,val);
				else
				{
					if(lc>=mid+1)	optrng(n[u].rs,lc,rc,val);
					else	optrng(n[u].ls,lc,mid,val),optrng(n[u].rs,mid+1,rc,val);
				}
				pull(u);
			}
		}
}xd;
class Tree
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn];
		int pre[maxn],en;
		int vis[maxn];
		
		void dfs1(int u,int f,int l)
		{
			fat[u]=f;	lev[u]=l;	cnt[u]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				dfs1(v,u,l+1);
				cnt[u]+=cnt[v];
			}
		}
		void dfs2(int u,int bf,int bl)
		{
			bfa[u]=bf;	ble[u]=bl;
			t2x[u]=xn;	x2t[xn]=u;	xn++;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(cnt[v]*2> cnt[u])	dfs2(v,bf,bl);
			}
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(cnt[v]*2<=cnt[u])	dfs2(v,v,bl+1); 
			}
		}
	public:
	int fat[maxn],lev[maxn],cnt[maxn];
		int bfa[maxn],ble[maxn];
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		void build()
		{
			memset(vis,0,sizeof vis);
			dfs1(0,-1,0);
			dfs2(0,0,0);
			xn--;
			xd.r=xd.build(0,xn);
		//	for(int i=0;i<n;i++)	cout<<i<<" "<<t2x[i]<<endl; 
		}
}tr;
int install(int u)
{
	int ans=0;
	while(u!=-1)
	{
	//	cout<<u<<" "<<tr.bfa[u]<<" "<<tr.fat[tr.bfa[u]]<<endl;
		ans+=xd.qrysum(xd.r,t2x[tr.bfa[u]],t2x[u]);
	//	cout<<t2x[u]<<"="<<t2x[tr.bfa[u]]<<endl;
		xd.optrng(xd.r,t2x[tr.bfa[u]],t2x[u],0);
		u=tr.fat[tr.bfa[u]];
	}
	return ans;
}
int uninstall(int u)
{
	int ans=tr.cnt[u];
//	cout<<t2x[u]+tr.cnt[u]<<"="<<endl;
	ans-=xd.qrysum(xd.r,t2x[u],t2x[u]+tr.cnt[u]-1);
	xd.optrng(xd.r,t2x[u],t2x[u]+tr.cnt[u]-1,1);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u;	scanf("%d",&u);
		tr.addedge(u,i);
	}
	tr.build();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		char cmd[10];	int x;	scanf("%s%d",cmd,&x);
		if(cmd[0]=='i')	printf("%d\n",install(x));
		if(cmd[0]=='u')	printf("%d\n",uninstall(x)); 
	//	cout<<"=="<<endl;
	}
}
