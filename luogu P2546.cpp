#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<map>
using namespace std;
struct Point
{
	int num,lev;
	int fee,val;
	vector <int> dp;
}p[500];
int pn=1;
struct Edge
{
	int v,next;
}e[1000];
int pre[1000];
int en=0;
map <string,int> book;
string s[1000],f[1000];
int n,m;
void addedge(int u,int v)
{
	e[en].v=v;e[en].next=pre[u];pre[u]=en++;
}
int cnt=0;
void dfs(int u)
{
	p[u].dp.resize(m+10);
	
	for(int i=pre[u];i!=-1;i=e[i].next)	dfs(e[i].v);
	
	
	p[u].dp[p[u].fee]=p[u].val;
	for(int i=pre[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		for(int j=m;j>=0;j--)
			for(int k=0;k<=j;k++)
				p[u].dp[j]=max(p[u].dp[j],p[u].dp[j-k]+p[v].dp[k]);
	}
	
}
void init()
{
	memset(pre,-1,sizeof pre);
	pn=1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		getchar();
		getline(cin,s[i]);	getline(cin,f[i]);
		book[s[i]]=pn;
		int l;	cin>>l;
		int fee[30],val[30];
		for(int j=1;j<=l;j++)	cin>>fee[j];
		for(int j=1;j<=l;j++)	cin>>val[j];
		for(int j=1;j<=l;j++)
		{
			p[pn].fee=fee[j];
			p[pn].val=val[j];
			p[pn].num=i;
			p[pn].lev=j;
			if(j!=1)	addedge(pn-1,pn);
			pn++;
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		if(f[i]=="")	addedge(0,book[s[i]]);
		else	addedge(book[f[i]],book[s[i]]);
	}
	cin>>m;
	for(int i=1;i<=n;i++)
	{
		int lev;	cin>>lev;
		for(int j=0;j<pn;j++)	if(p[j].num==i&&p[j].lev<=lev)	p[j].fee=0,p[j].val=0;
	}
}
int main()
{
	init();
	dfs(0);

	int ans=0;
	for(int i=0;i<=m;i++)
		ans=max(ans,p[0].dp[i]);
	cout<<ans<<endl; 
}
