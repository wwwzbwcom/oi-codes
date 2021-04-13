#include<iostream>
#include<cstring>
using namespace std;
int n,m,k,t;
int mar[100][100];
int map[100][100];
int buc[300];
int ans=1e9;
void dfs(int y,int x,int cur)
{
	if(cur>ans)	return;
	if(y==n+1)
	{
		for(int i=1;i<=x;i++)
		{
			memset(buc,0,sizeof buc);
			for(int j=1;j<=y;j++)	buc[map[j][i]]++;
			int mni=1e9,mxa=-1e9;
			for(int j=1;j<=200;j++)	mni=min(mni,buc[i]),mxa=max(mxa,buc[i]);
			cur+=mxa-mni;
		}
		ans=min(ans,cur);
		return;
	}
	if(x==m+1)
	{
		int mni=1e9,mxa=-1e9;
		for(int i=1;i<=200;i++)	mni=min(mni,buc[i]),mxa=max(mxa,buc[i]);
		cur+=mxa-mni;
		memset(buc,0,sizeof buc);
		dfs(y+1,x,cur);
	}
	else
	{
		if(mar[y][x])
		for(int i=1;i<=t;i++)
		{
			buc[i]++;
			map[y][x]=i;
			dfs(y,x+1,cur);
			map[y][x]=0;
			buc[i]--;
		}
	}
}
int main()
{
	cin>>n>>m>>k>>t;
	for(int i=1;i<=k;i++)
	{
		int x,y;	cin>>x>>y;
		mar[y][x]=1;
	}
	memset(buc,0,sizeof buc);
	dfs(1,1,0);
	cout<<ans<<endl;
}
