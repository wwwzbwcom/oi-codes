#include<algorithm>
#include<iostream>
using namespace std;
int n,m;
char map[50][50];
int vis[500]; 
int ans=0;
void dfs(int y,int x,int num)
{
	ans=max(ans,num);
	vis[map[y][x]]=1;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
			if(y+i>0&&x+j>0&&y+i<=n&&x+j<=m)
				if(abs(i)+abs(j)==1&&vis[map[y+i][x+j]]==0)
					dfs(y+i,x+j,num+1);
	vis[map[y][x]]=0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>map[i][j];
	dfs(1,1,1);
	cout<<ans<<endl; 
}
