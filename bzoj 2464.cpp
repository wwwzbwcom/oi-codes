#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=600;
int n,m;
int sy,sx;
int ey,ex;
char map[maxn][maxn];
int dis[maxn][maxn];
int inq[maxn][maxn];
void SPFA()
{
	for(int i=0;i<maxn;i++)	for(int j=0;j<maxn;j++)	dis[i][j]=2e9;
	queue <int> quy,qux;
	quy.push(sy);	qux.push(sx);	dis[sy][sx]=0;	inq[sy][sx]=1;
	while(!qux.empty())
	{
		int uy=quy.front(),ux=qux.front();	quy.pop(),qux.pop();	inq[uy][ux]=0;
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)	if(abs(i)+abs(j)==1)
			{
				int vy=uy+i,vx=ux+j,c;
				if(1<=vy&&vy<=n&&1<=vx&&vx<=m)
				{
					if(map[uy][ux]==map[vy][vx])	c=0;	else	c=1;
					if(dis[vy][vx]>dis[uy][ux]+c)
					{
						dis[vy][vx]=dis[uy][ux]+c;
						if(inq[vy][vx]==0)
						{
							inq[vy][vx]=1;
							quy.push(vy);	qux.push(vx);
						}
					}
				}
			}
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)&&n&&m)
	{
		for(int i=1;i<=n;i++)	scanf("%s",map[i]+1);
		scanf("%d%d",&sy,&sx);sy++;	sx++;
		scanf("%d%d",&ey,&ex);ey++;	ex++;
		SPFA();
		printf("%d\n",dis[ey][ex]);
	}
}
