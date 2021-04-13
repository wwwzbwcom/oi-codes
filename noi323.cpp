#include<iostream>
#include<cstring>
using namespace std;
int n,k;
int map[10][10];
int vis[10][10];
int	sb[10];
int dfs(int y,int c)
{
	if(y>n+1)	return 0;
	if(c==k)	return 1;
	int ans=0;
	ans+=dfs(y+1,c);
	for(int x=1;x<=n;x++)
		if(sb[x]==0&&map[y][x]==1)
		{
			sb[x]=1;
			ans+=dfs(y+1,c+1);
			sb[x]=0;
		}
	return ans;
}
int main()
{
	while(cin>>n>>k)
	{
		if(n==-1&&k==-1)	break;
		memset(map,0,sizeof map);
		memset(sb,0,sizeof sb);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				char t;
				cin>>t;
				if(t=='#')	map[i][j]=1;
				if(t=='.')	map[i][j]=0;
			}
		cout<<dfs(1,0)<<endl; 
	}
}
