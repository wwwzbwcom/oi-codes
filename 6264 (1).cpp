#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
int map[200][200];
int main()
{
	int yn,xn;
	int sy,sx,ey,ex;
	cin>>yn>>xn;
	memset(map,0,sizeof map);
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
		{
			char t;
			cin>>t;
			if(t!='#')	map[i][j]=1;
			if(t=='S')	sy=i,sx=j;
			if(t=='T')	ey=i,ex=j;
		}
	queue <int> y,x,t;
	y.push(sy);x.push(sx);t.push(0);
	while(!t.empty())
	{
		int yc=y.front(),xc=x.front(),tc=t.front();
		y.pop(),x.pop(),t.pop();
		if(yc==ey&&xc==ex)
		{
			cout<<tc;
			break;
		}
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
				if(abs(i)+abs(j)==1&&map[yc+i][xc+j]==1)
				{
					map[yc+i][xc+j]=0;
					y.push(yc+i);
					x.push(xc+j);
					t.push(tc+1);
				}
	}
}
