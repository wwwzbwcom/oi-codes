#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
const int oo=1e9;
using namespace std;
struct Edge
{
	int v,c;
	int nxt;
}e[1000000];
int pre[10000],en=0;
int yn,xn,d;
int sta,aim;
int tol=0;
char hei[100][100];
char thi[100][100];
int lev[10000];
void addedge(int u,int v,int c)
{
//	cout<<u<<" "<<v<<" "<<c<<endl; 
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
}
int idx(int y,int x)
{
	return y*xn+x;
}
void init()
{
	memset(pre,-1,sizeof pre);
	cin>>yn>>xn>>d;
	sta=xn*yn*2;
	aim=xn*yn*2+1;
	for(int y=0;y<yn;y++)
		for(int x=0;x<xn;x++)
			cin>>hei[y][x];
	for(int y=0;y<yn;y++)
		for(int x=0;x<xn;x++)
		{
			cin>>thi[y][x];
			if(thi[y][x]=='L')	tol++;
		}
	
	for(int y=0;y<yn;y++)
		for(int x=0;x<=xn;x++)
			if(hei[y][x]-'0'>0)
			{
			//	cout<<idx(y,x)*2<<" "<<idx(y,x)*2+1<<endl;
				addedge(idx(y,x)*2,idx(y,x)*2+1,hei[y][x]-'0');
				if(min(min(y+1,yn-y),min(x+1,xn-x))<=d)	addedge(idx(y,x)*2+1,aim,oo);
				if(thi[y][x]=='L')	addedge(sta,idx(y,x)*2,1);
			}
			
	for(int y=0;y<yn;y++)
		for(int x=0;x<xn;x++)
		{
			for(int ay=0;ay<yn;ay++)
				for(int ax=0;ax<xn;ax++)
					if(hei[y][x]-'0'>0&&hei[ay][ax]-'0'>0)
						if(abs(ay-y)+abs(ax-x)<=d&&(ax!=x||ay!=y))
						//	cout<<idx(y,x)*2+1<<" "<<idx(ay,ax)*2<<endl,
							addedge(idx(y,x)*2+1,idx(ay,ax)*2,oo);
		}
}
bool bfs()
{
	queue <int> q;	memset(lev,-1,sizeof lev);
	q.push(sta);	lev[sta]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		//cout<<u<<endl;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(lev[v]==-1&&c>0)
			{
				lev[v]=lev[u]+1;
				q.push(v);
			}
		}
	}
	if(lev[aim]==-1)	return 0;
	else	return 1;
}
int dfs(int u,int lc)
{
	int nc=0;
	if(u==aim)	return lc;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(lev[v]==lev[u]+1&&c>0)
		{
			int t=min(lc-nc,c);	t=dfs(v,t);	nc+=t;
			e[i].c-=t;	e[i^1].c+=t;
		}
	}
	if(nc==0)	lev[u]=-2;
	return nc;
}
int dinic()
{
	int ans=0;
	while(bfs())	ans+=dfs(sta,oo);
	return ans;
}
int main()
{
	init();
	cout<<tol-dinic();
}
