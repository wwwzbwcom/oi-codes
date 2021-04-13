#include<algorithm>
#include<iostream>
#include<string>
#include<map>
using namespace std;
const int maxn=300;
struct Edge
{
	int v,nxt;
}e[maxn*2];
int pre[maxn],en=0;
int n,m,s; 
string str;
int val[maxn];
int fat[maxn],lev[maxn];
int C[maxn][maxn];
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
void init()
{
	C[0][0]=1;
	for(int i=1;i<maxn;i++)
	{
		C[i][0]=1;
		for(int j=1;j<maxn;j++)	C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
void dfs(int u,int f,int l)
{
	fat[u]=f;	lev[u]=l;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f)	dfs(v,u,l+1);
	}
}
map <string,int> boo[maxn];
void getroute(int u,int v)
{
	string a,b;
	int an=0,bn=0;
	while(lev[u]>lev[v])	a+=str[u-1],u=fat[u];
	while(lev[v]>lev[u])	b+=str[v-1],v=fat[v];
	while(u!=v)	a+=str[u-1],b+=str[v-1],u=fat[u],v=fat[v];
	reverse(b.begin(),b.end());
	a+=b;
	boo[(a.size())][str]++;
}
int main()
{
	init();
	cin>>n>>m>>s;
	cin>>str;
	for(int i=1;i<=n;i++)	cin>>val[i];
	for(int i=1;i<=n-1;i++)
	{
		int u,v;	cin>>u>>v;
		addedge(u,v);
	}
	dfs(1,0,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			getroute(i,j);
	for(int i=1;i<=m;i++)
	{
		int k,t;	cin>>k>>t;
		int ans=1;
		for(map <int,string>::iterator i=boo[k].begin();i!=boo[k].end();i++)
		{
			if(*i>=t)	ans=ans*
		}
	}
}
