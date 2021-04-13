//#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=210;
int n,m,sy,sx,k;
char map[maxn][maxn];
int le[maxn],re[maxn],di[maxn];
int xd[]={0,0,0,-1,1};
int yd[]={0,-1,1,0,0};
bool vis[maxn][maxn][maxn];
int dyp[maxn][maxn][maxn];
int dfs(int t,int y,int x)
{
	if(vis[t][y][x])	return dyp[t][y][x];
	vis[t][y][x]=1;
	if(t==k+1)	return dyp[t][y][x]=0;
	
	int ans=0;
	int yv=y,xv=x,cnt=0;
	while(map[yv][xv]!='x'&&cnt<=re[t]-le[t]+1)
	{
		ans=max(ans,dfs(t+1,yv,xv)+cnt);
		yv+=yd[di[t]];
		xv+=xd[di[t]];
		cnt++;
	}
	return dyp[t][y][x]=ans;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&sy,&sx,&k);
	for(int i=0;i<maxn;i++)
		for(int j=0;j<maxn;j++)
			map[i][j]='x';
	for(int i=1;i<=n;i++)	scanf("%s",map[i]+1);
	for(int i=1;i<=n;i++)	map[i][m+1]='x';
	/*
	for(int i=0;i<=n+10;i++)
	{
		for(int j=0;j<=n+10;j++)
			cout<<map[i][j]<<" ";
		cout<<endl; 
	}
	*/
	
	for(int i=1;i<=k;i++)	scanf("%d%d%d",&le[i],&re[i],&di[i]);
	printf("%d",dfs(1,sy,sx));
}
