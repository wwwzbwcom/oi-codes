#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=10100;
int n,nn;
int xs,ys,xt,yt;
int a[maxn][5];
int b[maxn][5];
class SPFA
{
	private:
		class Edge
		{
			public:	int v,c,nxt;
		}e[maxn*5*50];
		int pre[maxn*5],en;
		long long dis[maxn*5];
		bool vis[maxn*5];
		void spfa()
		{
			queue <int> que; 
			for(int i=0;i<maxn;i++)	dis[i]=1e16;
			for(int i=0;i<nn;i++)
				if(b[i][0]==xs&&b[i][1]==ys)
				{
					dis[i*4]=0,
					vis[i*4]=1;
					que.push(i*4); 
				}
			while(!que.empty())
			{
				int u=que.front();	vis[u]=0;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(dis[v]>dis[u]+c)
					{
						dis[v]=dis[u]+c;
						if(vis[v]==0)
						{
							vis[v]=1;
							que.push(v);
						}
					}
				}
			}
		}
	public:
		SPFA()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		long long work()
		{
			spfa();
			for(int i=0;i<nn;i++)
				if(b[i][0]==xt&&b[i][1]==yt)
					return dis[i*4];
		}
}sp; 
void split(int p,int x,int y)
{
	int x0=a[p][0],y0=a[p][1],x1=a[p][2],y1=a[p][3];
	
	b[nn][0]=x0;	b[nn][1]=y;		b[nn][2]=x;		b[nn][3]=y1;	nn++;
	b[nn][0]=x;		b[nn][1]=y;		b[nn][2]=x1;	b[nn][3]=y1;	nn++;
	b[nn][0]=x0;	b[nn][1]=y0;	b[nn][2]=x;		b[nn][3]=y;		nn++;
	b[nn][0]=x;		b[nn][1]=y0;	b[nn][2]=x1;	b[nn][3]=y;		nn++;
	
}
int getdis(int x0,int y0,int x1,int y1)
{
	return abs(x0-x1)+abs(y0-y1);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	for(int j=0;j<3;j++)	cin>>a[i][j];
	cin>>xs>>xs>>yt>>yt;
	for(int i=0;i<n;i++)
	{
		if(a[i][0]<=xs&&xs<=a[i][2]&&a[i][1]<=ys&&ys<=a[i][3])	split(i,xs,ys);
		else
		{
			if(a[i][0]<=xt&&xt<=a[i][2]&&a[i][1]<=yt&&yt<=a[i][3])	split(i,xt,yt);
			else	memcpy(b[nn],a[i],12),nn++;	
		}
	}
	for(int k=1;k<nn;k++)
	{
		for(int i=0;i<3;i++)	if(i%2==0)
			for(int j=0;j<3;j++)	if(j%2==1)
				for(int p=0;p<3;p++)	if(p%2==0)
					for(int q=0;q<3;q++)	if(q%2==1)
						sp.addedge((k-1)*4+i*2+j,k*4+p*2+q,getdis(b[k-1][i],b[k-1][j],b[k][p],b[k][q]));
	}
	double v=0;
	cin>>v;
	cout<<v<<endl;
	cout<<(double)sp.work()/v<<endl;
}
