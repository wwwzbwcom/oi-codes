#include<iostream>
#include<cstdio>
using namespace std;
bool vis[6][16][16][16][16][16];
int dyp[6][16][16][16][16][16];
int k;
int c[10];
int s[10];
void dfs(int las,int c1,int c2,int c3,int c4,int c5)
{
	
	if(vis[las][c1][c2][c3][c4][c5]==1)	return;
	vis[las][c1][c2][c3][c4][c5]=1;
	if(las==1)
	{
		if(c1+1<=s[1]);	else	return;
		for(int i=0;i<=5;i++)
		{
			dfs(i,c1+1,c2,c3,c4,c5);
			if(i==2)	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1+1][c2][c3][c4][c5]*(c1);
			else	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1+1][c2][c3][c4][c5]*(c1+1);
			dyp[las][c1][c2][c3][c4][c5]%=1000000007;
		}
	}
	if(las==2)
	{
		if(c1-1>=0&&c2+1<=s[2]);	else	return;	
		for(int i=0;i<=5;i++)
		{
			dfs(i,c1-1,c2+1,c3,c4,c5);
			if(i==3)	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1-1][c2+1][c3][c4][c5]*(c2);
			else	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1-1][c2+1][c3][c4][c5]*(c2+1);
			dyp[las][c1][c2][c3][c4][c5]%=1000000007;
		}
	}
	if(las==3)
	{
		if(c2-1>=0&&c3+1<=s[3]);	else	return;
		for(int i=0;i<=5;i++)
		{
			dfs(i,c1,c2-1,c3+1,c4,c5);
			if(i==4)	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2-1][c3+1][c4][c5]*(c3);
			else	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2-1][c3+1][c4][c5]*(c3+1);
			dyp[las][c1][c2][c3][c4][c5]%=1000000007;
		}
	}
	if(las==4)
	{
		if(c3-1>=0&&c4+1<=s[4]);	else	return;
		for(int i=0;i<=5;i++)
		{
			dfs(i,c1,c2,c3-1,c4+1,c5);
			if(i==5)	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2][c3-1][c4+1][c5]*(c4);
			else	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2][c3-1][c4+1][c5]*(c4+1);
			dyp[las][c1][c2][c3][c4][c5]%=1000000007;
		}
	}
	if(las==5)
	{
		if(c4-1>=0&&c5+1<=s[5]);	else	return;
		for(int i=0;i<=5;i++)
		{
			dfs(i,c1,c2,c3,c4-1,c5+1);
		//	if(i==4)	dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2][c3][c4-1][c5+1]*(c5);
			dyp[las][c1][c2][c3][c4][c5]+=dyp[i][c1][c2][c3][c4-1][c5+1]*(c5+1);
			dyp[las][c1][c2][c3][c4][c5]%=1000000007;
		}
	}
	
//	if(dyp[las][c1][c2][c3][c4][c5])
//	cout<<las<<" "<<c1<<" "<<c2<<" "<<c3<<" "<<c4<<" "<<c5<<" "<<dyp[las][c1][c2][c3][c4][c5]<<endl;
}
int main()
{
	cin>>k;
	
	for(int i=1;i<=k;i++)
	{
		int t;cin>>t;c[t]++;
	}

	dyp[0][c[1]][c[2]][c[3]][c[4]][c[5]]=1;
	for(int i=5;i>=1;i--)	s[i]=s[i+1]+c[i];
	dfs(1,0,0,0,0,0);
	cout<<dyp[1][0][0][0][0][0];
}
