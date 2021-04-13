#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
const int maxn=60000;
const int oo=1e9;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int n,m,k;
int pre[maxn],en=0;
int siz[maxn];
int vis[maxn];
int dis[maxn];
map <int,int> buc;
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
int dfssize(int u,int f)
{
	siz[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f&&vis[v]==0)
		{
			dfssize(v,u);
			siz[u]+=siz[v];
		}
	}
	return siz[u];
}
int mni;
void dfsroot(int u,int f,int tot,int &root)
{
	int mxa=tot-siz[u];
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f&&vis[v]==0)
		{
			dfsroot(v,u,tot,root);
			mxa=max(mxa,siz[v]);
		}
	}
	if(mxa<mni)	mni=mxa,root=u;
}
int le,re;
void dfsdist(int u,int f,int d)
{
	dis[re++]=d;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&vis[v]==0)	dfsdist(v,u,d+c);
	}
}
bool cmp(const int &a,const int &b)
{
	return a>b;
}
int getans(int le,int re,int mod)
{
	sort(dis+le,dis+re,cmp);
	int ans=0,p=re-1;
	for(int i=le;i<re;i++)
	{
		while(p>i&&dis[i]+dis[p]<k)	p--;
		ans+=p-i;
		if(mod!=0)
		{
			for(int j=i+1;j<=p;j++)	buc[dis[i]+dis[j]]+=mod;//,cout<<dis[i]+dis[j]<<"=="<<mod<<endl;
		}
	}
	return ans;
}
int solve(int u,int mod)
{
	
	int ans=0;
	int tot=dfssize(u,0);
	int root;	mni=oo;	dfsroot(u,0,tot,root);
	vis[root]=1;
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]==0)	ans+=solve(v,mod);
	}
//	cout<<u<<"~"<<endl;
//	cout<<root<<" "<<ans<<endl;
	le=re=0;
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(vis[v]==0)
		{
			dfsdist(v,root,c);
		//	cout<<"==="<<endl;
			ans-=getans(le,re,-mod);
		//	cout<<root<<" "<<v<<" "<<dis[le]<<" "<<dis[re-1]<<" "<<ans<<endl;
			le=re;
		}
	}
	
	vis[root]=0;
	ans+=getans(0,re,mod);
//	cout<<root<<" "<<ans<<endl;
	for(int i=0;i<re;i++)
	{
		if(dis[i]>=k)
		{
			ans++;
			if(mod==1)	buc[dis[i]]++;
		}
		else	break;
	}
//	cout<<root<<" "<<ans<<endl;
	return ans;
}
int work(int lim,int mod)
{
	k=lim;
	if(solve(1,mod)>=m)	return 1;
	else	return 0;
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		addedge(u,v,c);
	}
//	k=1;	cout<<solve(1,0)<<endl;
//	cout<<"==============================="<<endl;
	
	int l=0,r=n,ans=0;
	while(l<=r)
	{
	//	cout<<l<<" "<<r<<endl;
		int mid=(l+r)/2;
		if(work(mid,0))	ans=mid,l=mid+1;
		else	r=mid-1;
	}
//	cout<<ans<<"========"<<endl;
	
	work(ans,1);
	map <int,int>::iterator i=buc.end();	i--;
	int j=0;
//	for(int i=0;i<=10;i++)	cout<<i<<" "<<buc[i]<<endl;
	while(j<m)
	{
		while(i->second>0)
		{
			i->second--;
			cout<<i->first<<endl;
			j++;
		}
		i--;
	}
}
