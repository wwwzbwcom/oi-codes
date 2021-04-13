#include<iostream>
using namespace std;
int n,m;
int map[100][100];
int vis[100][100];
int block=0;
int dfs(int y,int x)
{
	//cout<<y<<" "<<x<<endl;
	vis[y][x]=1;
	for(int i=-1;i<=1;i++)	for(int j=-1;j<=1;j++)
		if(vis[y+i][x+j]==0&&map[y+i][x+j]==1)
			dfs(y+i,x+j);
}
int main()
{
	cin>>n>>m;
	//cout<<"=========="<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char t;cin>>t;
			if(t=='W')	map[i][j]=1;
		}
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]==1&&vis[i][j]==0)
			{
				block++;
				//cout<<"============"<<endl;
				dfs(i,j);
			}
	cout<<block<<endl;
}
