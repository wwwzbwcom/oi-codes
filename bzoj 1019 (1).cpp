#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long f[50][50];
long long g[50][50];
bool vis[50][50];
int edg[10][2];
void dfs(int sta,int num)
{
	if(vis[sta][num])	return;
	vis[sta][num]=1;
	if(num==1)
	{
		f[sta][num]=1;
		for(int i=0;i<6;i++)
			if(edg[i][0]==sta)
			{
				g[sta][num]=edg[i][1];
				break;
			}
	}
	else
	{
		dfs(sta,num-1);
		int nxt=g[sta][num-1];
		dfs(nxt,num-1);
		if(sta==g[nxt][num-1])
		{
		//	cout<<sta<<" "<<nxt<<endl;
			f[sta][num]=f[sta][num-1]+1+f[nxt][num-1]+1+f[sta][num-1];
			g[sta][num]=nxt;
		}
		else
		{
			f[sta][num]=f[sta][num-1]+1+f[nxt][num-1];
			if(sta!=0&&nxt!=0)	g[sta][num]=0;
			if(sta!=1&&nxt!=1)	g[sta][num]=1;
			if(sta!=2&&nxt!=2)	g[sta][num]=2;
		}
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<6;i++)
	{
		char a,b;	cin>>a>>b;
		edg[i][0]=a-'A';
		edg[i][1]=b-'A';
	}
	dfs(0,n);
	cout<<f[0][n]<<endl;
}
