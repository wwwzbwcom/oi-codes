#include<algorithm>
#include<cstring>
#include<cstdio> 
using namespace std;
const int maxn=100100;
int val[maxn];
int idx[maxn];
int col[maxn];
struct XDS
{
	struct Node
	{
		int le,re;
		int ls,rs;
		long long val,ans,mul;
	}n[maxn*2];
	int nn,r;
	void pull(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		n[u].val=n[ls].val+n[rs].val;
		n[u].ans=n[ls].ans+n[ls].val*n[ls].mul+n[rs].ans+n[rs].val*n[rs].mul;
	}
	int build(int le,int re)
	{
	///	return 0; 
		int u=++nn;
		n[u].le=le;	n[u].re=re;
		n[u].val=0;	n[u].mul=0;
		if(le==re)	n[u].ls=n[u].rs=0,n[u].val=val[idx[le]];
		else
		{
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	void addmul(int u,int lc,int rc)
	{
		if(lc>rc)	swap(lc,rc);
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(lc==le&&rc==re)	n[u].mul++;
		else
		{
			if(rc<=mid)	addmul(n[u].ls,lc,rc);
			else
			{
				if(lc>=mid+1)	addmul(n[u].rs,lc,rc);
				else	addmul(n[u].ls,lc,mid),addmul(n[u].rs,mid+1,rc);
			}
			pull(u);
		}
	}
	pair <long long,long long> query(int u,int lc,int rc)
	{
		if(lc>rc)	swap(lc,rc);
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(lc==le&&rc==re)	return make_pair(n[u].val,n[u].ans+n[u].mul*n[u].val);
		else
		{
			long long val=0,ans=0;
			pair <long long,long long> tmp;
			if(rc<=mid)
			{
				tmp=query(n[u].ls,lc,rc);
				val=tmp.first;	ans=tmp.second+val*n[u].mul;
			}
			else
			{
				if(lc>=mid+1)
				{
					tmp=query(n[u].rs,lc,rc);
					val=tmp.first;	ans=tmp.second+val*n[u].mul;
				}
				else
				{
					tmp=query(n[u].ls,lc,mid);
					val+=tmp.first;	ans+=tmp.second;
					tmp=query(n[u].rs,mid+1,rc);
					val+=tmp.first;	ans+=tmp.second;
					ans+=val*n[u].mul;
				} 
			}
			return make_pair(val,ans);
		}
	}
}xds;
struct LCT
{
	LCT()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	struct Edge
	{
		int v,nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int cnt[maxn],fat[maxn],lev[maxn];
	long long dis[maxn];
	int blo[maxn],pos[maxn],pn;
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
	}
	void dfs1(int u,int f,int l,int d)
	{
		cnt[u]=1;	fat[u]=f;	lev[u]=l;	dis[u]=d;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f)	dfs1(v,u,l+1,d+val[v]),cnt[u]+=cnt[v];
		}
	}
	void dfs2(int u,int f,int ff,int l)
	{
		blo[u]=ff;	idx[pn]=u;	pos[u]=pn++;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f&&cnt[v]>cnt[u]/2)	dfs2(v,u,ff,l);
		}
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v!=f&&cnt[v]<=cnt[u]/2)	dfs2(v,u,v,l+1);
		}
	}
	void change(int u)
	{
		while(u!=-1)	xds.addmul(xds.r,pos[u],pos[blo[u]]),u=fat[blo[u]];
	}
	long long query(int u)
	{
		long long ans=0;
		while(u!=-1)	ans+=xds.query(xds.r,pos[u],pos[blo[u]]).second,u=fat[blo[u]];
		return ans;
	}
	
}lct;
int n,m;
int main()
{
//	freopen("color4.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
//	cout<<n<<endl;
	for(int i=1;i<=n-1;i++)
	{
		int v;	scanf("%d",&v);
		lct.addedge(i,v);
	}
	
//	cout<<"==="<<endl;
	for(int i=1;i<=n-1;i++)	scanf("%d",&val[i]);
	lct.dfs1(0,-1,0,0);
	
	lct.dfs2(0,-1,0,0); 
	
	xds.r=xds.build(0,n-1);
	long long cnt=0,sum=0; 
	
	for(int i=0;i<m;i++)
	{
		int cmd,x;	scanf("%d%d",&cmd,&x);
		if(cmd==1)
		{
			if(col[x]==0)
			{
				col[x]=1;
				lct.change(x);
				sum+=lct.dis[x];
				cnt++;
			}
		}
		if(cmd==2)	printf("%lld\n",cnt*lct.dis[x]+sum-2*lct.query(x));
	}
}
