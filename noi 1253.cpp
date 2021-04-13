#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int map[50][50][50];
int vis[50][50][50];
int zn,yn,xn;
int sz,sy,sx;
int ez,ey,ex;
int bfs()
{
	queue <int> z,y,x,t;
	z.push(sz);	y.push(sy);	x.push(sx);	t.push(0); vis[sz][sy][sx]=1;
	while(!t.empty())
	{
		int zc=z.front(),yc=y.front(),xc=x.front(),tc=t.front();
		z.pop();y.pop();x.pop();t.pop();
		if(zc==ez&&yc==ey&&xc==ex)	return tc;
		
		for(int i=-1;i<=1;i++)	for(int j=-1;j<=1;j++)	for(int k=-1;k<=1;k++)
			if(abs(i)+abs(j)+abs(k)==1&&map[zc+i][yc+j][xc+k]==1&&vis[zc+i][yc+j][xc+k]==0)
			{
				z.push(zc+i);y.push(yc+j);x.push(xc+k);t.push(tc+1);
				vis[zc+i][yc+j][xc+k]=1;
			}
	}
	return 1e9;
}
int main()
{
	while(cin>>zn>>yn>>xn,zn,yn,xn)
	{
		memset(vis,0,sizeof vis);
		for(int	z=0;z<50;z++)	for(int	y=0;y<50;y++)	for(int	x=0;x<50;x++)	map[z][y][x]=0;
		
		for(int z=1;z<=zn;z++)
			for(int y=1;y<=yn;y++)
				for(int x=1;x<=xn;x++)
				{
					char t;cin>>t;
					if(t=='#')	map[z][y][x]=0;	else	map[z][y][x]=1;
					if(t=='S')	sz=z,sy=y,sx=x;
					if(t=='E')	ez=z,ey=y,ex=x;	
				}
		int ans=bfs();
		if(ans==1e9)	cout<<"Trapped!"<<endl;
		else	cout<<"Escaped in "<<ans<<" minute(s)."<<endl;
	}
}
