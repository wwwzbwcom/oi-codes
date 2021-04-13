#include<algorithm> 
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2001;
int n,m;
bool sto[30][30];
bool map[maxn][maxn];
unsigned long long rot[4];
unsigned long long val[maxn][maxn];
bool vis[maxn][maxn][4];
int yt[]={0,0,-1,1},xt[]={-1,1,0,0};
short yq[maxn*maxn*4],xq[maxn*maxn*4],rq[maxn*maxn*4],tq[maxn*maxn*4];
int ys,ye,xs,xe,rs,re,ts,te;
char tmp[maxn];
int bfs()
{	
	yq[ye++]=0;	xq[xe++]=0;	rq[re++]=0;	tq[te++]=0;
	vis[0][0][0]=1;
	while(ts<=te)
	{
		int yc=yq[ys++],xc=xq[xs++],rc=rq[rs++],tc=tq[ts++];
		for(int i=0;i<=1;i++)
		{
			int p;
			if(i==0)	p=-1;	else	p=1;
			if((rot[(rc+p+4)%4]&val[yc][xc])==0)
			{
				if(vis[yc][xc][(rc+p+4)%4]==0)
				{
					vis[yc][xc][(rc+p+4)%4]=1;
					yq[ye++]=yc,xq[xe++]=xc,rq[re++]=(rc+p+4)%4,tq[te++]=tc+1;
				}
			}
		}
		for(int i=0;i<4;i++)	if(0<=yc+yt[i]&&yc+yt[i]<=n-m&&0<=xc+xt[i]&&xc+xt[i]<=n-m)
		{
			if((rot[rc]&val[yc+yt[i]][xc+xt[i]])==0)
			{
				if(vis[yc+yt[i]][xc+xt[i]][rc]==0)
				{
					vis[yc+yt[i]][xc+xt[i]][rc]=1;
					if(yc+yt[i]==n-m&&xc+xt[i]==n-m)	return tc+1;
					yq[ye++]=yc+yt[i],xq[xe++]=xc+xt[i],rq[re++]=rc,tq[te++]=tc+1; 
				}
			}
		}
	}
	return -1;
}
int main()
{
	cin>>n>>m;
//	getchar();
	for(int i=0;i<m;i++)
	{ 
		scanf("%s",tmp);
		for(int j=0;j<m;j++)
			sto[i][j]=tmp[j]-'0';
	//	getchar(); 
	} 
	//debug();
	
	for(int i=0;i<m;i++)	for(int j=0;j<m;j++)	if(sto[i][j])	rot[0]+=(1ull<<(i*m+j));
	for(int i=0;i<m;i++)	for(int j=0;j<m;j++)	if(sto[j][i])	rot[1]+=(1ull<<(i*m+(m-j-1)));
	for(int i=0;i<m;i++)	for(int j=0;j<m;j++)	if(sto[i][j])	rot[2]+=(1ull<<((m-i-1)*m+(m-j-1)));
	for(int i=0;i<m;i++)	for(int j=0;j<m;j++)	if(sto[j][i])	rot[3]+=(1ull<<((m-i-1)*m+j));
	
	for(int i=0;i<n;i++)
	{
		scanf("%s",tmp);
		for(int j=0;j<n;j++)
			map[i][j]=tmp[j]-'0';
	//	getchar();
	}
	
	/*for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<map[i][j]<<" ";
		cout<<endl;
	}
	*/
	for(int i=0;i<=n-m;i++)
		for(int j=0;j<=n-m;j++)
			for(int p=0;p<m;p++)
				for(int q=0;q<m;q++)
					if(map[i+p][j+q])	val[i][j]+=(1ull<<(p*m+q));
	cout<<bfs()<<endl;
}
