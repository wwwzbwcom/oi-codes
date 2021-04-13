#include<iostream>
#include<cstring>
using namespace std;
const int maxn=100100; 
struct Splay
{
	struct Node
	{
		Node *ls,*rs;
		int wei,ans;
		int mxa,cnt;
		Node(int weii,int ansi)
		{
			ls=rs=NULL;
			wei=weii;
			ans=mxa=ansi;
			cnt=1;
		}
	};
	Node *r;
	Splay()
	{
		r=NULL;
	}
	void pull(Node *u)
	{
		if(u==NULL)	return;
		u->mxa=u->ans;
		u->cnt=1;
		if(u->ls!=NULL)	u->mxa=max(u->mxa,u->ls->mxa),u->cnt+=u->ls->cnt;
		if(u->rs!=NULL) u->mxa=max(u->mxa,u->rs->mxa),u->cnt+=u->rs->cnt;
	}
	void lrotate(Node *&u)
	{
		Node *rs=u->rs;	u->rs=rs->ls;	rs->ls=u;	pull(u);	pull(rs);	u=rs; 
	}
	void rrotate(Node *&u)
	{
		Node *ls=u->ls;	u->ls=ls->rs;	ls->rs=u;	pull(u);	pull(ls);	u=ls; 
	}
	void insert(Node *&u,int wei,int ans)
	{
		if(u==NULL)	u=new Node(wei,ans);
		else
		{
			if( wei < u->wei )	insert(u->ls,wei,ans),rrotate(u);
			else	insert(u->rs,wei,ans),lrotate(u);
		}
	}
	void copy(Node *u,Splay *a)
	{
		if(u==NULL)	return;
		else
		{
			a->insert(a->r,u->wei,u->ans);
			copy(u->ls,a);
			copy(u->rs,a);
		}
	}
};
Splay *merge(Splay *a,Splay *b)
{
	if(a->r==NULL)
	{
		delete a; 
		return b;
	}
	else
	{
		if(b->r==NULL)
		{
			delete b;
			return a;
		}
	}
	if(a->r->cnt > b->r->cnt)
	{
		b->copy(b->r,a);
		delete b;
		return a;
	}
	else
	{
		a->copy(a->r,b);
		delete a;
		return b;
	}
}
struct Edge
{
	int v,nxt;
}e[maxn];
int pre[maxn],en=0;
int wei[maxn];
int ans[maxn];
Splay *spl[maxn];
int n;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
}
void dfs(int u)
{
	spl[u]=new Splay;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		dfs(v);
		spl[u]=merge(spl[u],spl[v]);
	}
	spl[u]->insert(spl[u]->r,wei[u],0);
	if(spl[u]->r->ls==NULL)	spl[u]->r->ans=1;
	else	spl[u]->r->ans=spl[u]->r->ls->mxa+1;
	ans[u]=spl[u]->r->ans;
	spl[u]->pull(spl[u]->r);
}
int main()
{
//	freopen("reward1.in","r",stdin);
	memset(pre,-1,sizeof pre);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int u;	cin>>u;
		if(i!=1)	addedge(u,i);
	}
	for(int i=1;i<=n;i++)	cin>>wei[i];
	dfs(1);
	for(int i=1;i<=n;i++)	cout<<ans[i]<<" ";
}
