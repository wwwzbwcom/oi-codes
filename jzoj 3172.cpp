#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
const int maxn=500100;

struct XDS
{
	struct Node
	{
		Node()
		{
			ls=rs=NULL;
			le=re=0;
			set=0;
		}
		Node *ls,*rs;
		int le,re;
		int set;
	};
	Node *r;
	Node *build(int le,int re)
	{
		Node *u=new Node;
		u->le=le;	u->re=re;
		u->set=0;
		if(le!=re)
		{
			int mid=(le+re)/2;
			u->ls=build(le,mid);
			u->rs=build(mid+1,re);
		}
		return u;
	}
	void set(Node *u,int lc,int rc)
	{
		int le=u->le,re=u->re;
	//	cout<<lc<<" "<<rc<<endl; 
		int mid=(le+re)/2;
		if(lc==le&&rc==re)	u->set=1;
		else
		{
			if(rc<=mid)	set(u->ls,lc,rc);
			else
			{
				if(lc>=mid+1)	set(u->rs,lc,rc);
				else	set(u->ls,lc,mid),set(u->rs,mid+1,rc);
			}
		}
	}
	int query(Node *u,int p)
	{
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
		if(le==re)	return u->set;
		else
		{
			if(u->set)	return 1;
			int mid=(le+re)/2;
			if(p<=mid)	return query(u->ls,p);
			else	return query(u->rs,p);
		}
	}
}xds;

int cnt=0;
struct AC
{
	struct Node
	{
		int nxt[26];
		int fail;
		int end;
	}n[4000000];
	int r,nn;
	AC()
	{
		r=++nn;
	}
	void insert(char str[])
	{
		int len=strlen(str);
		int u=r;
		for(int i=0;i<len;i++)
		{
			if(n[u].nxt[str[i]-'a']==0)	n[u].nxt[str[i]-'a']=++nn;
			u=n[u].nxt[str[i]-'a'];
		}
		n[u].end=max(n[u].end,len);
	}
	void build()
	{
		queue <int> que;
		for(int i=0;i<26;i++)
		{
			if(n[r].nxt[i]==0)	n[r].nxt[i]=r;
			else	n[n[r].nxt[i]].fail=r,que.push(n[r].nxt[i]);
		}
		int tmp=r;
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=0;i<26;i++)
			{
				if(n[u].nxt[i]==0)	n[u].nxt[i]=n[n[u].fail].nxt[i];
				else	n[n[u].nxt[i]].fail=n[n[u].fail].nxt[i],que.push(n[u].nxt[i]);
			}
			int tmp=u;
			while(tmp!=r)
			{
				n[u].end=max(n[u].end,n[tmp].end);
				tmp=n[tmp].fail;
			}
		}
	}
	void match(char str[])
	{
		int len=strlen(str);
		int u=r;
		for(int i=0;i<len;i++)
		{
			u=n[u].nxt[str[i]-'a'];
			if(n[u].end!=0)	xds.set(xds.r,i-n[u].end+1,i);
			//cout<<i-n[u].end+1<<" "<<i<<endl;
			//cout<<i-tmp->end+1<<" "<<i<<endl;
		}
	}
}ac;
int n,m;
int ans;
char a[maxn];
char b[maxn];
int main()
{
//	freopen("poplocavanje.in","r",stdin);
	scanf("%d",&n);
	ans=n;
	xds.r=xds.build(0,n);
	scanf("%s",a);
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s",b);
		ac.insert(b);
	}
	ac.build();
	ac.match(a);
	for(int i=0;i<n;i++)	if(xds.query(xds.r,i))	ans--;
	printf("%d",ans);
//	while(1);
}
