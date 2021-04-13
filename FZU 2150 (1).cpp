#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
int x[3][200];
int y[3][200];
int cnt[3];
int map[20][20];
int vis[20][20];
int vis0[3][2000][20][20];
int block,n,m,gn,flag=0;
int C=0;
void dfs(int a,int b)
{
	x[block][cnt[block]]=a;
	y[block][cnt[block]++]=b;
	vis[a][b]=block;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
			if(abs(i)+abs(j)==1&&map[a+i][b+j]==1&&vis[a+i][b+j]==0)
				dfs(a+i,b+j);
}
int bfs(int a,int blo)
{
	queue <int> x0,y0,t;
	x0.push(x[blo][a]);
	y0.push(y[blo][a]);
	t.push(0);
	int times=0;
	while(!t.empty())
	{
		int xc=x0.front(),yc=y0.front(),tc=t.front();
		vis0[blo][a][xc][yc]=tc;
		x0.pop();y0.pop();t.pop();
	//	cout<<xc<<" "<<yc<<" "<<tc<<endl;
		times=max(times,tc);
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
				if(abs(i)+abs(j)==1&&map[xc+i][yc+j]==1&&vis0[blo][a][xc+i][yc+j]==-1)
				{
					vis0[blo][a][xc+i][yc+j]=tc+1;
					x0.push(xc+i);
					y0.push(yc+j);
					t.push(tc+1);
				}
	}
	return times;
}
void init()
{
	memset(cnt,0,sizeof cnt);
	memset(map,0,sizeof map);
	memset(vis,0,sizeof vis);
	memset(vis0,-1,sizeof vis0);
	flag=0,block=0;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&gn);
	while(gn--)
	{
		init();
		scanf("%d%d",&n,&m);
		getchar();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				char t;
				scanf("%c",&t);
				//cout<<t<<endl;
				if(t=='#') map[i][j]=1;
			}
			getchar();
		}
		
		for(int i=1;i<=n;i++)
		{ 
			for(int j=1;j<=m;j++)
				if(vis[i][j]==0&&map[i][j]==1)
				{
					++block;
					if(block>2)
					{
						printf("Case %d: %d\n",++C,-1);
						//cout<<"Case "<<++C<<": "<<-1<<endl;
						flag=1;
						break;
					}
					dfs(i,j);
				}
			if(flag==1) break; 
		} 
		if(flag==1) continue;
		if(block==1)
		{
			int ans=999999999;
			for(int i=0;i<cnt[1];i++) int t=bfs(i,1);
			for(int i=0;i<cnt[1];i++)
				for(int j=0;j<cnt[1];j++)
				{
					int temp=0;
					for(int a=0;a<cnt[1];a++)
					{
						int xc=x[1][a];
						int yc=y[1][a];
						temp=max(temp,min(vis0[1][i][xc][yc],vis0[1][j][xc][yc]));
					}
					ans=min(temp,ans);
				}
			printf("Case %d: %d\n",++C,ans);
		}
		if(block==2)
		{
			int ans1,ans2;
			ans1=ans2=999999999;
			for(int i=0;i<cnt[1];i++)
				ans1=min(ans1,bfs(i,1));
		//	cout<<11111<<endl;
			for(int i=0;i<cnt[2];i++)
				ans2=min(ans2,bfs(i,2));
		//	cout<<ans1<<" "<<ans2<<endl;
			printf("Case %d: %d\n",++C,max(ans1,ans2));
		}
	}
}
