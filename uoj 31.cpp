#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200;
char str[maxn];
int vis[maxn][maxn];
int dyp[maxn][maxn][2];
void dfs(int l,int r)
{
	if(vis[l][r])	return;
	vis[l][r]=1;
	
	if(r-l+1<=2)
	{
		if(r-l+1==1)	return;
		else
		{
			if(str[l]=='('&&str[r]==')')	dyp[l][r][0]=0,dyp[l][r][1]=1;
			if(str[l]==')'&&str[r]=='(')	dyp[l][r][0]=1,dyp[l][r][1]=0;
			return;
		}
	}
	for(int i=l;i<r;i++)
	{
		dfs(l,i);	dfs(i,r);
		dyp[l][r][0]=min(dyp[l][r][0],min(dyp[l][i][0],dyp[l][i][1]+1)+min(dyp[i+1][r][0],dyp[i+1][r][1]+1));
		dyp[l][r][1]=min(dyp[l][r][1],min(dyp[l][i][0]+1,dyp[l][i][0])+min(dyp[i+1][r][1]+1,dyp[i+1][r][1]));
	}
	dfs(l+1,r-1);
	if(str[l]=='('&&str[r]==')')	dyp[l][r][0]=min(dyp[l][r][0],min(dyp[l+1][r-1][0],dyp[l+1][r-1][1]+1));
	if(str[l]==')'&&str[r]=='(')	dyp[l][r][1]=min(dyp[l][r][1],min(dyp[l+1][r-1][0]+1,dyp[l+1][r-1][1]));
	
	dyp[l][r][0]=min(dyp[l][r][0],dyp[l][r][1]+1);
	dyp[l][r][1]=min(dyp[l][r][1],dyp[l][r][0]+1);
}
int main()
{
	cin>>str;
	int len=strlen(str);
	for(int i=0;i<maxn;i++)
		for(int j=0;j<maxn;j++)
			dyp[i][j][0]=dyp[i][j][1]=1e9;
	dfs(0,len-1);
	cout<<dyp[0][len-1][0]<<endl;
}
