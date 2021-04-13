#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
char tmp[150];
int sto[150][150];
int vis[150][150];
int mty[150][150],mtx[150][150];
int tol,ans=0;
int maxMatch(int y,int x)
{
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)	if(abs(i)+abs(j)==1)
		{
			if(sto[y+i][x+j]=='.'&&vis[y+i][x+j]==0)
			{
				vis[y+i][x+j]=1;
				if(mty[y+i][x+j]==0||maxMatch(mty[y+i][x+j],mtx[y+i][x+j]))
				{
					mty[y+i][x+j]=y;
					mtx[y+i][x+j]=x;
					return 1;
				}
			}
		}
	return 0;
}
void moreWays(int y,int x)
{
	vis[y][x]=1;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)	if(abs(i)+abs(j)==1)
			if(sto[y+i][x+j]=='.'&&mty[y+i][x+j]!=0&&vis[mty[y+i][x+j]][mtx[y+i][x+j]]==0)
				moreWays(mty[y+i][x+j],mtx[y+i][x+j]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int y=1;y<=n;y++)
	{
		char tmp[150];	scanf("%s",tmp+1);
		for(int x=1;x<=m;x++)
			sto[y][x]=tmp[x];
	}
	for(int y=1;y<=n;y++)
		for(int x=1;x<=m;x++)
			if(sto[y][x]=='.')
			{
				memset(vis,0,sizeof vis);
				tol++;
				ans+=maxMatch(y,x);
			}
	if(ans==tol)	printf("LOSE\n");
	else
	{
		printf("WIN\n");
		memset(vis,0,sizeof vis);
		for(int y=1;y<=n;y++)
			for(int x=1;x<=m;x++)
				if(sto[y][x]=='.'&&mty[y][x]==0)
					moreWays(y,x);
		for(int y=1;y<=n;y++)
			for(int x=1;x<=m;x++)
				if(vis[y][x])	printf("%d %d\n",y,x);
	}
}
