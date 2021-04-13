#include<iostream>
#include<cstring>
using namespace std;
int n,m;
bool vis[2000000][2];
bool dyp[2000000][2];
char map[20][20];

inline void workl(int con[20][20],int y,int x)
{
	int ty=y,tx=x;
	while(0<=ty&&ty<n&&0<=tx&&tx<m&&!con[ty][tx])	con[ty][tx]=1,ty--,tx--;
	ty=y;tx=x;	con[y][x]=0;
	while(0<=ty&&ty<n&&0<=tx&&tx<m&&!con[ty][tx])	con[ty][tx]=1,ty++,tx++;
	con[y][x]=0;
}
inline void workr(int con[20][20],int y,int x)
{
//	cout<<y<<"="<<x<<endl;
	int ty=y,tx=x;
	while(0<=ty&&ty<n&&0<=tx&&tx<m&&!con[ty][tx])	con[ty][tx]=1,ty--,tx++;
	ty=y;tx=x;	con[y][x]=0;
	while(0<=ty&&ty<n&&0<=tx&&tx<m&&!con[ty][tx])	con[ty][tx]=1,ty++,tx--;
	con[y][x]=0;
}
void dfs(int uc,int un)
{
	if(vis[uc][un])	return;
	vis[uc][un]=1;
	if(uc==(1<<(n*m))-1)
	{
		//cout<<uc<<"!!!"<<un<<endl;
		dyp[uc][un]=0;
		return;
	}
	int tmp=uc;
	int con[20][20];
	int bac[20][20];
//	cout<<uc<<"============================"<<un<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			bac[i][j]=con[i][j]=tmp%2,tmp/=2;
		//	cout<<con[i][j]<<" ";
		}
		//cout<<endl;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)	if(con[i][j]==0)
		{
			int vc=0,vn=un^1;
			if(map[i][j]=='L')	workl(con,i,j),con[i][j]=1;
			if(map[i][j]=='R')	workr(con,i,j),con[i][j]=1;
			if(map[i][j]=='X')	workl(con,i,j),workr(con,i,j),con[i][j]=1;
			for(int p=0;p<n;p++)
				for(int q=0;q<m;q++)
					if(con[p][q])	vc+=(1<<(p*m+q));
			dfs(vc,vn);
			memcpy(con,bac,sizeof con);
			if(dyp[vc][vn]==0)
			{
				dyp[uc][un]=1;
				return;
			}
			 
		}
//	cout<<uc<<"@@@"<<un<<endl;
	dyp[uc][un]=0;
}
int main()
{
	while(cin>>n>>m)
	{
		memset(vis,0,sizeof vis);
		memset(dyp,0,sizeof dyp);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cin>>map[i][j];
		dfs(0,0);
		if(dyp[0][0])	cout<<"WIN"<<endl;
		else	cout<<"LOSE"<<endl;
	}
}
