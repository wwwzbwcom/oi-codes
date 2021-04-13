#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int dyp*;
bool vis*;
int m,r,g,b;
int ans=0;
void dfs(r,g,b,i)
{
	if(vis[r][g][b][i])	return;
	
}
int main()
{
	dyp=(int*)malloc(500000*100*(sizeof int));
	cin>>m>>r>>g>>b;
	for(int i=0;i<81;i++)	if(check(i))	vis[getr(i)][getg(i)][getb(i)][i]=1,dyp[getr(i)][getg(i)][getb(i)][i]=1;
	for(int i=0;i<81;i++)	if(check(i))	dfs(r,g,b,i),ans+=dyp[r][g][b][i];
	cout<<ans<<endl;
}
