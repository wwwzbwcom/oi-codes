#include<iostream>
using namespace std;
int n,m;
int sta,end;
int wei[10][10];
int dyp[1200000][2];
bool vis[1200000][2];
void dfs(int uc,int up,int lev)
{
	if(vis[uc][up]==1)	return;
	vis[uc][up]=1;
	if(uc==(1<<(n*m))-1)
	{
		dyp[uc][up]=0;
		return;
	}
	int tmp=uc;
	bool col[10][10];
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)	col[i][j]=tmp%2,tmp/=2;
	int lef=0;
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			if(col[i][j]==0||col[i+1][j]==0||col[i][j+1]==0||col[i+1][j+1]==0)
				lef+=wei[i][j];
	if(lef==0)	return;
	
	if(up==0)	dyp[uc][up]=-1e9;	else	dyp[uc][up]=1e9;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)	if(col[i][j]==0)
		{
			int vc=uc,vp=up^1;
			col[i][j]=1;	vc+=(1<<(i-1)*m+(j-1));
			int ans=0;
			if(col[i-1][j-1]&&col[i-1][j]&&col[i][j-1]&&col[i][j])	ans+=wei[i-1][j-1];
			if(col[i-1][j]&&col[i-1][j+1]&&col[i][j]&&col[i][j+1])	ans+=wei[i-1][j];
			if(col[i][j-1]&&col[i][j]&&col[i+1][j-1]&&col[i+1][j])	ans+=wei[i][j-1];
			if(col[i][j]&&col[i][j+1]&&col[i+1][j]&&col[i+1][j+1])	ans+=wei[i][j];
			if(ans)	vp^=1;
			dfs(vc,vp,lev+1);
			if(up==0)	dyp[uc][up]=max(dyp[uc][up],ans+dyp[vc][vp]);	else	dyp[uc][up]=min(dyp[uc][up],-ans+dyp[vc][vp]);
			col[i][j]=0;
			
			if(up==0)
			{
				if(dyp[uc][up]==lef)	return;
			}
			else
			{
				if(dyp[uc][up]==-lef)	return;
			}
			
		}
}
int main()
{
	freopen("in.txt","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int val;	cin>>val;
			if(val==1)	sta+=1<<((i-1)*m+(j-1));
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++) 
			cin>>wei[i][j];
//	cout<<sta<<endl;
	dfs(sta,0,0);
//	for(int i=0;i<(1<<(n*m));i++)	cout<<i<<" "<<dyp[i][0]<<" "<<dyp[i][1]<<endl;
	cout<<dyp[sta][0]<<endl;
}
