#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
int gn;
int p,q;
int x[]={-2,-2,-1,-1,+1,+1,+2,+2};
int y[]={-1,+1,-2,+2,-2,+2,-1,+1};
int vis[100][100];
int oy[1000],ox[1000];
int dfs(int yc,int xc,int num)
{
	oy[num]=yc;ox[num]=xc;
	vis[yc][xc]=1;
	if(num==p*q)	return 1;

	for(int i=0;i<8;i++)	if(yc+y[i]>0&&xc+x[i]>0&&yc+y[i]<=p&&xc+x[i]<=q)
	if(vis[yc+y[i]][xc+x[i]]==0&&dfs(yc+y[i],xc+x[i],num+1))	return 1;
	
	vis[yc][xc]=0;
	return 0;
}
int main()
{
	cin>>gn;
	int g=0;
	while(gn--)
	{
		g++;
		memset(vis,0,sizeof vis);	int flag=0;
		cin>>p>>q;
		cout<<"Scenario #"<<g<<":"<<endl;
		for(int i=1;i<=p;i++)
			for(int j=1;j<=q;j++)
				if(dfs(i,j,1))
				{
					for(int i=1;i<=p*q;i++)
					{
						char t=ox[i]+'A'-1;
						cout<<t<<oy[i];
					}
					flag=1;
					break;
				}
		
		if(flag==0)	cout<<"impossible"<<endl;
		else	cout<<endl;
		cout<<endl;
	}
}
