#include<iostream>
#include<cstring>
using namespace std;
int map[100][100];
int vis[100][100];
int dfs(int y,int x)
{
	vis[y][x]=1;
	int ans=0;
	if(map[y][x-1]==1&&vis[y][x-1]==0)	ans+=dfs(y,x-1);
	if(map[y][x+1]==1&&vis[y][x+1]==0)	ans+=dfs(y,x+1);
	if(map[y-1][x]==1&&vis[y-1][x]==0)	ans+=dfs(y-1,x);
	if(map[y+1][x]==1&&vis[y+1][x]==0)	ans+=dfs(y+1,x);
	return ans+1;
}
int main()
{
	int xn,yn;
	while(cin>>xn>>yn,xn,yn)
	{
		memset(map,0,sizeof map);
		memset(vis,0,sizeof vis);
		int sy,sx;
		for(int i=1;i<=yn;i++)
			for(int j=1;j<=xn;j++)
			{
				char t;
				cin>>t;
				if(t=='#')	map[i][j]=0;
				if(t=='.')	map[i][j]=1;
				if(t=='@')	map[i][j]=1,sy=i,sx=j;
			}
		cout<<dfs(sy,sx)<<endl;
	}
}
