#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int gn;
int n,m;
int dyp[20][20][5000];
bool vis[20][20][5000];
int dfs(int np,int mp,int con)
{
	if(vis[np][mp][con])	return dyp[np][mp][con];
	vis[np][mp][con]=true;
	
	int tmp=0;
	for(int i=np;i<n;i++)	if((con&(1<<i))==0)	tmp++;
	if(mp>m)	return dyp[np][mp][con]=0;
	if(mp+tmp<m)	return dyp[np][mp][con]=0;
	if(np==n)
	{
		if(mp==m)	return dyp[np][mp][con]=1;
		else	return dyp[np][mp][con]=0;
	}
	
	int ans=0;
	if((con&(1<<np))==0)	ans+=dfs(np+1,mp+1,(con|(1<<np)));
	for(int i=0;i<n;i++)	if((con&(1<<i))==0&&i!=np)	ans+=dfs(np+1,mp,(con|(1<<i)));
	return dyp[np][mp][con]=ans;
}
int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n>>m;
		memset(dyp,0,sizeof dyp);
		memset(vis,0,sizeof vis);
		cout<<dfs(0,0,0)<<endl;
	}
}
