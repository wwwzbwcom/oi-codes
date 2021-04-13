#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1e5+100;
int n,q;
struct Graph
{
	Graph(){memset(p,-1,sizeof p);}
	struct Edge
	{
		int v,nxt;
	}e[maxn];
	int p[maxn],w[maxn],n;
	void ae(int u,int v)
	{
		e[n].v=v;e[n].nxt=p[u];p[u]=n++;
		e[n].v=u;e[n].nxt=p[v];p[v]=n++;
	}
}g;
int cnt[maxn],lev[maxn];
void init(int u,int f,int d)
{
	cnt[u]=0;	lev[u]=d;
	for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
	{
		int v=g.e[i].v;
		if(v!=f)	init(v,u,d+1),cnt[u]+=cnt[v];	
	}
	cnt[u]++;
}
int blo[maxn],fat[maxn],ffa[maxn];
int cur,sto[maxn],idx[maxn];
void divide(int u,int f,int ff)
{
	blo[u]=ff;	fat[u]=f;	ffa[u]=fat[ff];
	cur++;	sto[cur]=u;	idx[u]=cur;
	//cout<<cur<<" "<<u<<endl;
	for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
	{
		int v=g.e[i].v;
		if(v!=f)	if(cnt[v]>cnt[u]/2)	divide(v,u,ff);
	}
	for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
	{
		int v=g.e[i].v;
		if(v!=f)	if(cnt[v]<=cnt[u]/2)	divide(v,u,v);
	}
}
struct XDS
{
	struct Node
	{
		int ls,rs;
		int le,re;
		int mxa,sum;
	}n[maxn];
	int nn;
	void update(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		n[u].mxa=max(n[ls].mxa,n[rs].mxa);
		n[u].sum=n[ls].sum+n[rs].sum;
	//	cout<<n[u].le<<"="<<n[u].re<<" "<<n[ls].mxa<<" "<<n[rs].mxa<<endl; 
	}
	int build(int le,int re)
	{
		int now=++nn;
		n[now].le=le;	n[now].re=re;
		if(le==re)
		{
			n[now].ls=n[now].rs=0;
			n[now].mxa=n[now].sum=g.w[sto[le]];
		}
		else
		{
			int mid=(le+re)/2;
			n[now].ls=build(le,mid);
			n[now].rs=build(mid+1,re);
			update(now);
		}
		return now;
	}
	void change(int now,int aim,int val)
	{
		int le=n[now].le,re=n[now].re;
		int ls=n[now].ls,rs=n[now].rs;
		int mid=(le+re)/2;
	//	cout<<le<<" "<<re<<" "<<mid<<endl;
		if(le==re)	n[now].mxa=n[now].sum=val;
		else
		{
			if(aim<=mid)	change(ls,aim,val);
			else	change(rs,aim,val);
			update(now);
		}
	}
	int quemax(int now,int lq,int rq)
	{
		if(lq>rq)	swap(lq,rq); 
		int le=n[now].le,re=n[now].re;
		int ls=n[now].ls,rs=n[now].rs;
		int mid=(le+re)/2;
		if(lq==le&&rq==re)	return n[now].mxa;
		else
		{
			if(rq<=mid)	return quemax(ls,lq,rq);
			else
			{
				if(lq>=mid+1)	return quemax(rs,lq,rq);
				else	return max(quemax(ls,lq,mid),quemax(rs,mid+1,rq));
			}
		}
	}
	int quesum(int now,int lq,int rq)
	{
		if(lq>rq)	swap(lq,rq);
		int le=n[now].le,re=n[now].re;
		int ls=n[now].ls,rs=n[now].rs;
		int mid=(le+re)/2;
		if(lq==le&&rq==re)	return n[now].sum;
		else
		{
			if(rq<=mid)	return quesum(ls,lq,rq);
			else
			{
				if(lq>=mid+1)	return quesum(rs,lq,rq);
				else	return quesum(ls,lq,mid)+quesum(rs,mid+1,rq);
			}
		}
	}
}x;
void change(int u,int v)
{
	x.change(1,idx[u],v);
}
int quemax(int u,int v)
{
	int ans=-1e9;
	while(blo[u]!=blo[v])
	{
		if(lev[u]>lev[v])	ans=max(ans,x.quemax(1,idx[u],idx[blo[u]])),u=ffa[u];
		else				ans=max(ans,x.quemax(1,idx[v],idx[blo[v]])),v=ffa[v];
	//	cout<<u<<" "<<v<<" "<<blo[u]<<" "<<blo[v]<<endl;
	}
	ans=max(ans,x.quemax(1,idx[u],idx[v]));
	return ans;
}
int quesum(int u,int v)
{
	int ans=0;
	while(blo[u]!=blo[v])
	{
		if(lev[u]>lev[v])	ans+=x.quesum(1,idx[u],idx[blo[u]]),u=ffa[u];
		else				ans+=x.quesum(1,idx[v],idx[blo[v]]),v=ffa[v];
	}
	ans+=x.quesum(1,idx[u],idx[v]);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		g.ae(u,v);
	}
	init(1,-1,0);
	divide(1,-1,1);
	for(int i=1;i<=n;i++)	cout<<i<<" "<<blo[i]<<" "<<ffa[i]<<endl;
	for(int i=1;i<=n;i++)	scanf("%d",&g.w[i]);
	x.build(1,n);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		char cmd[10];int u,v;	scanf("%s%d%d",cmd,&u,&v);
		if(cmd[1]=='H')	change(u,v);
		if(cmd[1]=='M')	printf("%d\n",quemax(u,v));
		if(cmd[1]=='S')	printf("%d\n",quesum(u,v));
	}
}
