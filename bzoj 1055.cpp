#include<iostream>
#include<map>
using namespace std;
int num[10];
char idx[500];
char edg[10][10][10];
int dyp[250][250][10];
int vis[250][250];
string str;
void dfs(int l,int r)
{
	if(vis[l][r]==1)	return;
	vis[l][r]=1;
	int len=r-l+1;
	if(len==1)	dyp[l][r][str[l]]=1;
	for(int p=l;p<r;p++)
	{
		dfs(l,p);
		dfs(p+1,r);
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				if(dyp[l][p][i]==1&&dyp[p+1][r][j]==1)
				{
					for(int k=1;k<=4;k++)
						if(edg[i][j][k]!=0)	dyp[l][r][k]=1;
				}
	}
}
int main()
{
	idx['W']=1;	idx['I']=2;	idx['N']=3;	idx['G']=4;
	cin>>num[1]>>num[2]>>num[3]>>num[4];
	for(int i=1;i<=4;i++)
		for(int j=1;j<=num[i];j++)
		{
			char a,b;cin>>a>>b;
			edg[idx[a]][idx[b]][i]=1;
		}
	cin>>str;
	for(int i=0;i<str.size();i++)	str[i]=idx[str[i]];
	dfs(0,str.size()-1);
	if(dyp[0][str.size()-1][1]==1)	cout<<"W";
	if(dyp[0][str.size()-1][2]==1)	cout<<"I";
	if(dyp[0][str.size()-1][3]==1)	cout<<"N";
	if(dyp[0][str.size()-1][4]==1)	cout<<"G";
}
