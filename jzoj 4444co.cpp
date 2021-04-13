#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=250100;
int n,m,q;
int les,equ,mor;
int val[maxn];
int t2x[maxn],x2t[maxn],xn;
class Nodein
{
	public:
		int ls,rs;
		int sum; 
}in[(1<<17)*17*17];
int inn;
class LCT
{
	private:
		class XDSout
		{
			protected:
				
			private:
				class XDSin
				{
					public:
						int r;
						void optadd(int u,int le,int re,int pos,int val)
						{
							int mid=(le+re)>>1;
							if(le==re)	in[u].sum+=val;
							else
							{
								if(in[u].ls==0)	in[u].ls=++inn;
								if(in[u].rs==0)	in[u].rs=++inn;
								
								if(pos<=mid)	optadd(in[u].ls,le,mid,pos,val);
								else	optadd(in[u].rs,mid+1,re,pos,val);
								
								in[u].sum=in[in[u].ls].sum+in[in[u].rs].sum;
							}
						}
						int qrysum(int u,int le,int re,int lc,int rc)
						{
							if(u==0)	return 0; 
							int mid=(le+re)>>1;
							if(le==lc&&re==rc)	return in[u].sum;
							else
							{
								if(rc<=mid)	return qrysum(in[u].ls,le,mid,lc,rc);
								else
								{
									if(lc>=mid+1)	return qrysum(in[u].rs,mid+1,re,lc,rc);
									else	return qrysum(in[u].ls,le,mid,lc,mid)+qrysum(in[u].rs,mid+1,re,mid+1,rc);
								}
							}
						}
				};
				class Node
				{
					public: 
						Node *ls,*rs;
						XDSin in;
				};
			public:
				Node *r;
				Node *build(int le,int re)
				{
					Node *u=new Node;
					int mid=(le+re)>>1;
					u->in.r=++inn;
					for(int i=le;i<=re;i++)	u->in.optadd(u->in.r,1,m,val[x2t[i]],1);
					if(le==re)	u->ls=u->rs=0;
					else
					{
						u->ls=build(le,mid);
						u->rs=build(mid+1,re);
					}
					return u;
				}
				void optadd(Node *u,int le,int re,int pos,int val)
				{
					int mid=(le+re)>>1;
					u->in.optadd(u->in.r,1,m,val,1);
					if(le==re)	return;
					else
					{
						if(pos<=mid)	optadd(u->ls,le,mid,pos,val);
						else	optadd(u->rs,mid+1,re,pos,val);
					}
				}
				int qrysum(Node *u,int le,int re,int lc,int rc,int lci,int rci)
				{
					int mid=(le+re)>>1;
					if(le==lc&&re==rc)	return u->in.qrysum(u->in.r,1,m,lci,rci);
					else
					{
						if(rc<=mid)	return qrysum(u->ls,le,mid,lc,rc,lci,rci);
						else
						{
							if(lc>=mid+1)	return qrysum(u->rs,mid+1,re,lc,rc,lci,rci);
							else	return qrysum(u->ls,le,mid,lc,mid,lci,rci)+qrysum(u->rs,mid+1,re,mid+1,rc,lci,rci);
						}
					}
				}
		}xd;
		class Tree
		{
			private:
				class Edge
				{
					public:
						int v,nxt;
				}e[maxn*2];
				int pre[maxn],en;
				int cnt[maxn];
				void dfslc1(int u,int f,int l)
				{
					cnt[u]=1;	fat[u]=f;	lev[u]=l;
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v;
						if(v!=f)	dfslc1(v,u,l+1),cnt[u]+=cnt[v];
					}
				}
				void dfslc2(int u,int f,int ff,int l)
				{
					bfa[u]=ff;	ble[u]=l;	xn++;	t2x[u]=xn;	x2t[xn]=u;
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v;
						if(v!=f&&cnt[v]>cnt[u]/2)	dfslc2(v,u,ff,l);
					}
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v;
						if(v!=f&&cnt[v]<=cnt[u]/2)	dfslc2(v,u,v,l+1); 
					}
				}
			public:
				int fat[maxn],lev[maxn];
				int bfa[maxn],ble[maxn];
				Tree()
				{
					memset(pre,-1,sizeof pre);
				}
				void addedge(int u,int v)
				{
					e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
					e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
				}
				void build()
				{
					dfslc1(1,-1,1);
					dfslc2(1,-1,1,1);
				}
		}tr;
	public:
		
		void addedge(int u,int v)
		{
			tr.addedge(u,v);
		}
		void build()
		{
			tr.build();
			xd.r=xd.build(1,n);
		//	cout<<"-======"<<endl;
		//	for(int i=1;i<=n;i++)	xd.optadd(xd.r,1,n,t2x[i],val[i]);
		}
		inline void query(int u,int v,int k)
		{
			les=equ=mor=0;
			while(1)
			{
				if(tr.bfa[u]==tr.bfa[v])
				{
					if(tr.lev[v]>tr.lev[u])	swap(u,v);
					
					if(k>1)			les+=xd.qrysum(xd.r,1,n,t2x[v],t2x[u],1,min(m,k-1));
					if(1<=k&&k<=m)	equ+=xd.qrysum(xd.r,1,n,t2x[v],t2x[u],k,k);
					if(k<m)			mor+=xd.qrysum(xd.r,1,n,t2x[v],t2x[u],max(1,k+1),m);
					
					break;
				}
				else
				{
					if(tr.ble[v]>tr.ble[u])	swap(u,v);
					
					if(k>1)			les+=xd.qrysum(xd.r,1,n,t2x[tr.bfa[u]],t2x[u],1,min(m,k-1));
					if(1<=k&&k<=m)	equ+=xd.qrysum(xd.r,1,n,t2x[tr.bfa[u]],t2x[u],k,k);
					if(k<m)			mor+=xd.qrysum(xd.r,1,n,t2x[tr.bfa[u]],t2x[u],max(1,k+1),m);
					
					u=tr.fat[tr.bfa[u]];
				}
			}
			printf("%d %d %d\n",les,equ,mor);
		}
}lc;
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)	scanf("%d",&val[i]);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		lc.addedge(u,v);
	}
	lc.build();
	for(int i=1;i<=q;i++)
	{
		int x,y,k;	scanf("%d%d%d",&x,&y,&k);
		int la=(les^equ^mor);
		x^=la;	y^=la;	k^=la;
//		cout<<"========"<<la<<endl;
		lc.query(x,y,k);
	}
}
