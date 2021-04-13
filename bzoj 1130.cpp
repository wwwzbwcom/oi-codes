#include<iostream>
using namespace std;
int n,m;
int edg[50];
int vis[50];
int dig[300000];
int ans=1e9;
int output;
int digit(int num)
{
	return dig[num&((1<<13)-1)]+dig[num>>13];
}
void dfs(int cur,int cnt,int con,int num)
{
	if(cnt==n/2&&cur==n)
	{
	//	cout<<con<<" "<<num<<endl;
		if(ans>num)
		{	
			ans=num;
			output=con;
		}
		return;
	}
	if(cur==n)	return;
	dfs(cur+1	, cnt+1	, con+(1<<cur)	, num+digit( (con^((1<<cur)-1))&edg[cur]	));
	dfs(cur+1	, cnt	, con			, num+digit( con&edg[cur] 		));
}
int main()
{
	for(int i=0;i<(1<<13);i++)	dig[i]=dig[(i>>1)]+(i&1);
	
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int u,v;cin>>u>>v;
		u--;v--;
		edg[u]|=(1<<v);edg[v]|=(1<<u);
	}
	dfs(0,0,0,0);
//	cout<<ans<<endl;
	for(int i=0;i<n;i++)	if((output&(1<<i)))	cout<<i+1<<" ";
}
