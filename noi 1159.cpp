#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n,m;
char map[100][100];
bool vis[100][100];
int total[500];
int reach[500];
int glovi[100][100];
int sy,sx;
int ey,ex;
void dfs(int y,int x)
{
	if(glovi[y][x]==0)	reach[map[y][x]]++;
	glovi[y][x]=1;
	vis[y][x]=1;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
			if(abs(i)+abs(j)==1&&vis[y+i][x+j]==0&&map[y+i][x+j]!='X')
			{
				char cur=map[y+i][x+j];
				if(cur=='.')	dfs(y+i,x+j);
				if(cur=='G')	dfs(y+i,x+j);
				if('a'<=cur&&cur<='z')	dfs(y+i,x+j);
				if('A'<=cur&&cur<='E'&&total[cur+32]==reach[cur+32])	dfs(y+i,x+j);
			}
}
int main()
{
	while(cin>>n>>m,n,m)
	{
		ey=0;ex=0;
		memset(reach,0,sizeof reach);
		memset(total,0,sizeof total);
		memset(glovi,0,sizeof glovi);
		for(int i=0;i<100;i++)	for(int j=0;j<100;j++)	map[i][j]='X';
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				cin>>map[i][j];
				if(map[i][j]=='S')	sy=i,sx=j;
				if(map[i][j]=='G')	ey=i,ex=j; 
				total[map[i][j]]++;
			}
		for(int i=1;i<=6;i++)
		{
			memset(vis,0,sizeof vis);
			dfs(sy,sx);
		}
		if(vis[ey][ex]==1)	cout<<"YES"<<endl;
		else	cout<<"NO"<<endl;
	}
}
