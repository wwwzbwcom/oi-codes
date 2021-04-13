#include<iostream>
using namespace std;
int m,r,g,b;
int map[10][100];
int ans=0;
void dfs(int np,int mp)
{
	if(np==2)
	{
		for(int i=0;i<m-1;i++)	if(map[0][i]==map[0][i+1])	return;
		for(int i=0;i<m-1;i++)	if(map[1][i]==map[1][i+1])	return;
		for(int i=0;i<m;i++)	if(map[0][i]==map[1][i])	return;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<m;j++)
				cout<<map[i][j];
			cout<<endl;
		}
		cout<<"====="<<endl;;
		ans++;
		return;
	}
	if(mp==m)
	{
		dfs(np+1,0);
		return;
	}
	if(r)	map[np][mp]=1,r--,dfs(np,mp+1),r++,map[np][mp]=0;
	if(g)	map[np][mp]=2,g--,dfs(np,mp+1),g++,map[np][mp]=0;
	if(b)	map[np][mp]=3,b--,dfs(np,mp+1),b++,map[np][mp]=0;
}
int main()
{
	cin>>m>>r>>g>>b;
	dfs(0,0);
	cout<<ans<<endl;
}
