#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int oo=999999999;
int map[200][200];
int vis0[200][200];


int vis[200];
int low[200];
int e[200][200];
int idx[200][200];
int gn,x,y,cnt;
void bfs(int a,int b)
{
	memset(vis0,0,sizeof vis0);
	queue <int> x,y,t;
	x.push(a);y.push(b);t.push(0);
	vis0[b][a]=1;
	while(!t.empty())
	{
		int xc=x.front(),yc=y.front(),tc=t.front();
		x.pop();y.pop();t.pop();
		//cout<<xc<<" "<<yc<<" "<<tc<<" "<<vis0[yc][xc]<<endl;
		if(idx[yc][xc])
		{
		//	cout<<idx[b][a]<<" "<<idx[yc][xc]<<" "<<tc<<endl;
			e[idx[yc][xc]][idx[b][a]]=e[idx[b][a]][idx[yc][xc]]=min(e[idx[yc][xc]][idx[b][a]],tc);
		}
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
				if(abs(i)+abs(j)==1)
				{
					if(map[yc+i][xc+j]&&vis0[yc+i][xc+j]==0)
					{
						vis0[yc+i][xc+j]=1;
						x.push(xc+j);
						y.push(yc+i);
						t.push(tc+1);
					}
				}
	}
}
void init()
{
	for(int i=0;i<200;i++) for(int j=0;j<200;j++) e[i][j]=oo;
	memset(map,0,sizeof map);
	memset(vis,0,sizeof vis);
	memset(idx,0,sizeof idx);
	cnt=0;
}
int prim()
{
	vis[1]=1;
	int ans=0;
	for(int i=1;i<=cnt;i++) low[i]=e[1][i];
	for(int i=1;i<cnt;i++)
	{
		int uv=oo,v;
		for(int j=1;j<=cnt;j++) if(vis[j]==0&&low[j]<uv) uv=low[j],v=j;
		vis[v]=1;ans+=uv;
		for(int j=1;j<=cnt;j++) if(low[j]>e[v][j]) low[j]=e[v][j];
	}
	return ans;
}
int main()
{
	cin>>gn;
	while(gn--)
	{
		init();
		cin>>x>>y;
	//	get();
		for(int i=1;i<=y;i++)
		{
			while(getchar()!='\n');
			for(int j=1;j<=x;j++)
			{
				char t;
				cin.get(t);
			//	cout<<i<<" "<<j<<" "<<t<<endl;
				if(t=='#') map[i][j]=0;
				else if(t==' ') map[i][j]=1;
					 else map[i][j]=2,idx[i][j]=++cnt;
			}
			
		}
		for(int i=1;i<=y;i++)
			for(int j=1;j<=x;j++)
			{
				if(map[i][j]==2)
				{
				//	cout<<j<<"===="<<i<<endl;
					bfs(j,i);
				}
			}
		/*
		for(int i=1;i<=cnt;i++)
		{
			for(int j=1;j<=cnt;j++)
				cout<<e[i][j]<<" ";
			cout<<endl;
		}
		*/
		cout<<prim()<<endl;
	}
 } 
