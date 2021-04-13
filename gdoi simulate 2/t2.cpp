#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;
const int maxn=100100;
struct Splay
{
	struct Node
	{
		int ls,rs;
		int wei,ans;
		int add,cnt,mxa;
	};
	int r,nn;
	int num;
	Splay(int siz,int numi)
	{
		num=numi;
		r=nn=0;
		for(int i=0;i<=siz;i++)	n.push_back(Node(0,0,0));
	}
	int size()const
	{
		return n[r].cnt;
	}
	void push(int u)
	{
		n[u].ans+=n[u].add;
		if(n[u].ls!=0)	n[n[u].ls].add+=n[u].add;
		if(n[u].rs!=0)	n[n[u].rs].add+=n[u].add;
		n[u].add=0;
	}
	void pull(int u)
	{
		if(u==0)	return;
		n[u].mxa=n[u].ans;
		if(n[u].ls!=0)	n[u].mxa=max(n[u].mxa,n[n[u].ls].mxa);
		if(n[u].rs!=0)	n[u].mxa=max(n[u].mxa,n[n[u].rs].mxa);
		n[u].cnt=1;
		if(n[u].ls!=0)	n[u].cnt+=n[n[u].ls].cnt;
		if(n[u].rs!=0)	n[u].cnt+=n[n[u].rs].cnt;
	}
	void lrotate(int &u)
	{
		int rs=n[u].rs;	n[u].rs=n[rs].ls;	n[rs].ls=u;	pull(u);	pull(rs);	u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;	n[u].ls=n[ls].rs;	n[ls].rs=u;	pull(u);	pull(ls);	u=ls;
	}
	void insert(int &u,int wei,int ans)
	{
		if(u==0)
		{
			u=++nn;
			n[u]=Node(wei,ans,1); 
		}
		else
		{
			push(u);
			if(wei<n[u].wei)	insert(n[u].ls,wei,ans),rrotate(u);
			else	insert(n[u].rs,wei,ans),lrotate(u);
		}
	}
	void go(int u)
	{
		push(u);
		
		if(n[u].ls!=0)	go(n[u].ls);
		if(n[u].rs!=0)	go(n[u].rs);
		
		pull(u);
	}
	
};
Splay merge(Splay &a,Splay &b)
{
	cout<<"=========="<<endl;
	if(a.size()<b.size())
	{
		a.go(a.r);cout<<"==========="<<b.num<<" "<<b.nn<<" "<<b.size()<<endl;
		for(int i=1;i<=a.nn;i++)	cout<<i<<" "<<a.nn<<endl,b.insert(b.r,a.n[i].wei,a.n[i].ans);
		return b;
	}
	else
	{
		b.go(a.r);cout<<"==========="<<a.nn<<" "<<a.size()<<endl;
		for(int i=1;i<=b.nn;i++)	cout<<i<<" "<<b.nn<<endl,a.insert(a.r,b.n[i].wei,b.n[i].ans);
		return a;
	}
	
}
stack <Splay> sp;
struct Edge
{
	int v,nxt;
}e[maxn];
int pre[maxn],en=0;
int wei[maxn];
int cnt[maxn];
int ans[maxn];
int n;
void addedge(int u,int v)
{
	//cout<<u<<"="<<v<<endl;
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
}
void dfs1(int u)
{
	cnt[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;	dfs1(v);
		cnt[u]+=cnt[v];
	}
}
void dfs2(int u)
{
	Splay cur(cnt[u],u);
	cout<<u<<endl;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;	dfs2(v);
		Splay tmp=sp.top();
		cout<<u<<" "<<v<<"("<<endl;
		cur=merge(cur,tmp);
		cout<<u<<")"<<endl;
		sp.pop();
	}
	cout<<u<<endl;
	cur.insert(cur.r,wei[u],0);
	cout<<u<<endl;
	cur.n[cur.r].ans=cur.n[cur.n[cur.r].ls].mxa+1;
	ans[u]=cur.n[cur.r].ans;
	cur.pull(cur.r);
	sp.push(cur);
}
struct Edge
{
	int v,nxt;
}e[maxn];
int pre[maxn],en=0;
int wei[maxn];
int ans[maxn];
int n;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
}
void dfs(int u)
{
	Splay cur=new Splay;
}
int main()
{
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
