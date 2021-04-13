#include<iostream>
using namespace std;
int vis[100][100];
int wall[100][100];
int dfs(int yc,int xc)
{
	
	vis[yc][xc]=1;
	int t=wall[yc][xc];
	int w,n,e,s;
	w=t%2;t/=2;
	n=t%2;t/=2;
	e=t%2;t/=2;
	s=t%2;t/=2;
	int ans=0;
	if(w==0&&vis[yc][xc-1]==0)	ans+=dfs(yc,xc-1);
	if(n==0&&vis[yc-1][xc]==0)	ans+=dfs(yc-1,xc);
	if(e==0&&vis[yc][xc+1]==0)	ans+=dfs(yc,xc+1);
	if(s==0&&vis[yc+1][xc]==0)	ans+=dfs(yc+1,xc);
	return ans+1;
}
int main()
{
	int yn,xn;
	cin>>yn>>xn;
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
			cin>>wall[i][j];
	int ans=0,block=0;
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
			if(vis[i][j]==0)
			{
				block++;
				ans=max(ans,dfs(i,j));
			}
	cout<<block<<endl<<ans<<endl;
}
