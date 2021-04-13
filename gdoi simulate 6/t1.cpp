#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
char map[100][100];
int boo[100][100];
int ans=1e9;
void dfs(int y,int x,int pos,int mod,int sy,int sx,int lim);
void work(int pos,int lim);
void dfs(int y,int x,int pos,int mod,int sy,int sx,int len,int lim)
{
	if(pos>=ans)	return;
	boo[y][x]=1;
//	cout<<y<<" "<<x<<" "<<len<<" "<<mod<<endl;
	int flag=0;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)	if(abs(i)+abs(j)==1&&boo[y+i][x+j]==0&&map[y+i][x+j]=='.'&&(1<=y+i&&y+i<=n&&1<=x+j&&x+j<=m))
		{
			flag=1;
			dfs(y+i,x+j,pos,mod,sy,sx,len+1,lim);
			if(pos>=ans)	return;
		}
//	cout<<y<<" "<<x<<" "<<len<<" "<<flag<<" "<<mod<<endl;
	if(flag==0)
	{ 
		if(mod==0&&(y==1||y==n||x==1||x==m)&&(y!=sy||x!=sx)&&len>=1)	work(pos+1,lim);
		if(mod==1&&abs(y-sy)+abs(x-sx)==1&&len>=3)	work(pos,lim);
	}
	boo[y][x]=0;
	
}
void work(int pos,int lim)
{
	
//	getchar();
	if(pos>lim)	return;
	int flag=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]!='#'&&boo[i][j]==0)	flag=1;
	if(flag==0)
	{
		ans=min(pos,ans);
	//	cout<<ans<<endl;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(boo[i][1]==0&&map[i][1]=='.')	dfs(i,1,pos,0,i,1,0,lim);
		if(boo[i][m]==0&&map[i][m]=='.')	dfs(i,m,pos,0,i,m,0,lim);
	}
	for(int i=2;i<=m-1;i++)
	{
		if(boo[1][i]==0&&map[1][i]=='.')	dfs(1,i,pos,0,1,i,0,lim);
		if(boo[n][i]==0&&map[n][i]=='.')	dfs(n,i,pos,0,n,i,0,lim);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(boo[i][j]==0&&map[i][j]=='.')
				dfs(i,j,pos,1,i,j,0,lim);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>map[i][j];
	for(int i=0;i<20;i++)
	{
		cout<<i<<endl;
		work(0,i);
		if(ans!=1e9)	break;
	}
	if(ans==1e9)	cout<<"-1"<<endl;
	else	cout<<ans<<endl; 
}
