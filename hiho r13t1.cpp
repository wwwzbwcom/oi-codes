#include<iostream>
using namespace std;
const int maxn=1100;
int n;
int a[maxn];
int dyp[maxn][maxn];
int vis[maxn][maxn]; 
int dfs(int l,int r)
{
	if(vis[l][r])	return dyp[l][r];
	vis[l][r]=1;
	int con=(n-(r-l+1))%2;
	
	if(l==r)
	{
		if(con)	return dyp[l][r]=0;
		else	return dyp[l][r]=a[l];
	}
	else
	{
		if(con)	return dyp[l][r]=min(dfs(l+1,r),dfs(l,r-1));
		else	return dyp[l][r]=max(dfs(l+1,r)+a[l],dfs(l,r-1)+a[r]);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	dfs(1,n);
	cout<<dyp[1][n]<<endl;
}
