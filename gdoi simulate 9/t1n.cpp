#include<iostream>
#include<cstring>
using namespace std;
int n,m;
char map[50][50];
int ney[50][50];
int nex[50][50];
char bla[50][50];
int by,bx;
char whi[50][50];
int wy,wx;
char opt[50][50];
int oy,ox;
int dyp[20][20][20][20];
int vis[20][20][20][20];
int dfs(int y1,int x1,int y2,int x2)
{
	if(!(y1<=y2&&x1<=x2&&0<=y1&&y1<oy&&0<=x1&&x1<ox&&0<=y2&&y2<oy&&0<=x2&&x2<ox))
	{
	//	cout<<"=="<<endl;
		return 0;
	}
	if(vis[y1][x1][y2][x2])	return dyp[y1][x1][y2][x2];
	
	
	vis[y1][x1][y2][x2]=1;
	
	int boo[100];	memset(boo,0,sizeof boo);
	for(int i=y1;i<=y2;i++)
		for(int j=x1;j<=x2;j++)
		{
			if(opt[i][j]=='L')
				boo[dfs(y1,x1,i-1,x2)^dfs(i+1,x1,y2,x2)]=1;
			if(opt[i][j]=='R')
				boo[dfs(y1,x1,y2,j-1)^dfs(y1,j+1,y2,x2)]=1;
			if(opt[i][j]=='X')
				boo[dfs(y1,x1,i-1,j-1)^dfs(y1,j+1,i-1,x2)^dfs(i+1,x1,y2,j-1)^dfs(i+1,j+1,y2,x2)]=1;
		}
	for(int i=0;i<100;i++)	if(boo[i]==0)
	{
	//	cout<<y1<<" "<<x1<<" "<<y2<<" "<<x2<<" "<<i<<endl;
		return	dyp[y1][x1][y2][x2]=i;
	}
}
int main()
{
	while(cin>>n>>m)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cin>>map[i][j];
		
		for(int i=-m+1;i<n;i++)
			for(int j=0;j<n+m;j++)
				if(0<=i+j&&i+j<n)	ney[i+j][j]=i+m-1;
		for(int i=-m+1;i<n;i++)
			for(int j=0;j<n+m;j++)
				if(0<=i+j&&i+j<n)	nex[i+j][m-j-1]=i+m-1;
		/*
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout<<ney[i][j]<<" ";
			cout<<endl; 
		}
		cout<<"==========="<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout<<nex[i][j]<<" ";
			cout<<endl; 
		}
		*/
		memset(bla,0,sizeof bla);
		by=bx=-1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if((i%2+j%2)%2==1)
					bla[ney[i][j]/2][nex[i][j]/2]=map[i][j],by=max(by,ney[i][j]/2),bx=max(bx,nex[i][j]/2);
		by++;	bx++;
		memset(whi,0,sizeof whi);
		wy=wx=-1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if((i%2+j%2)%2==0)
					whi[ney[i][j]/2][nex[i][j]/2]=map[i][j],wy=max(wy,ney[i][j]/2),wx=max(wx,nex[i][j]/2);
		wy++;	wx++;
		/*
		cout<<by<<" "<<bx<<endl;
		for(int i=0;i<by;i++)
		{
			for(int j=0;j<bx;j++)	cout<<bla[i][j];
			cout<<endl; 
		}
		cout<<wy<<" "<<wx<<endl;
		for(int i=0;i<wy;i++)
		{
			for(int j=0;j<wx;j++)	cout<<whi[i][j];
			cout<<endl; 
		}
		*/
		int b=0,w=0;
		memcpy(opt,bla,sizeof opt);	oy=by;	ox=bx;
		memset(vis,0,sizeof vis);
		memset(dyp,0,sizeof dyp);
		b=dfs(0,0,oy-1,ox-1);
		/*
		cout<<oy<<" "<<ox<<endl;
		for(int i=0;i<oy;i++)
		{
			for(int j=0;j<ox;j++)
				cout<<opt[i][j];
			cout<<endl;
		}
		
		cout<<"======================"<<endl;
		*/
		memcpy(opt,whi,sizeof opt);	oy=wy;	ox=wx;
		memset(vis,0,sizeof vis);
		memset(dyp,0,sizeof dyp);
		w=dfs(0,0,oy-1,ox-1);
		/*
		cout<<oy<<" "<<ox<<endl;
		for(int i=0;i<oy;i++)
		{
			for(int j=0;j<ox;j++)
				cout<<opt[i][j];
			cout<<endl;
		}
		cout<<b<<" "<<w<<endl;
		*/
		if((b^w))	cout<<"WIN"<<endl;
		else	cout<<"LOSE"<<endl;
	}
}
