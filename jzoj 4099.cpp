#include<iostream>
using namespace std;
int n,k;
bool vis[20];
int dfs(int p,int c)
{
	if(p==n)	return c;
	int ans=0;
	for(int i=0;i<n;i++)	if(vis[i]==0)
	{
		vis[i]=1;
		if(i<=p)	ans+=dfs(p+1,c+1);
		else		ans+=dfs(p+1,c);
		vis[i]=0;
	}
	return ans;
}
int main()
{
//	cout<<(15ll*qsm(15ll,mod-2))%mod<<endl; 
	cin>>n>>k;
	cout<<dfs(0,0);
}
