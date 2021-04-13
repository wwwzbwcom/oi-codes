#include<cstdio>
#include<cstring>
using namespace std;
char map[50][50];
int vis[50][50];
int mat[50][50][2];
int xd[]={0,0,-1,1};
int yd[]={-1,1,0,0};
int con[1500];
int n,m;
int yc,xc,k;
int dfs(int yu,int xu)
{
	if(map[yu][xu]=='.')	return 0;
	for(int i=0;i<4;i++)
	{
		int yv=yu+yd[i],xv=xu+xd[i];
		if(map[yu][xu]!=map[yv][xv]&&vis[yv][xv]==0&&map[yv][xv]!='.')
		{
			vis[yv][xv]=1;
			if(mat[yv][xv][0]==0||dfs(mat[yv][xv][0],mat[yv][xv][1]))
			{
				mat[yv][xv][0]=yu;
				mat[yv][xv][1]=xu;
				mat[yu][xu][0]=yv;
				mat[yu][xu][1]=xv;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<50;i++)	for(int j=0;j<50;j++)	map[i][j]='.';
	for(int i=1;i<=n;i++)
	{
		scanf("%s",map[i]+1);	map[i][m+1]='.';
		for(int j=1;j<=m;j++)	if(map[i][j]=='.')	yc=i,xc=j,map[i][j]='X';
	//	printf("%s",map[i]+1);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mat[i][j][0]==0)
			{
				memset(vis,0,sizeof vis);
				dfs(i,j);
			}
	scanf("%d",&k);
	for(int i=1;i<=2*k;i++)
	{
		map[yc][xc]='.';
		if(mat[yc][xc][0]!=0)
		{
			int yt=mat[yc][xc][0],xt=mat[yc][xc][1];
			mat[yc][xc][0]=mat[yc][xc][1]=0;
			mat[yt][xt][0]=mat[yt][xt][1]=0;
			memset(vis,0,sizeof vis);
			con[i]=dfs(yt,xt)^1;
		}
		scanf("%d%d",&yc,&xc);
		//cout<<yc<<" "<<xc<<endl;
	}
	//for(int i=1;i<=2*k;i++)	cout<<i<<"="<<con[i]<<endl;
	int ans=0;
	for(int i=1;i<=2*k;i++)	if(i%2==1)	if(con[i]==1&&con[i+1]==1)	ans++;
	printf("%d\n",ans);
	for(int i=1;i<=2*k;i++)	if(i%2==1)	if(con[i]==1&&con[i+1]==1)	printf("%d\n",i/2+1);
}

