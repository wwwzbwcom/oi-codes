#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int n;
int boo[10000];
int vis[100];
int sto[100];
void pt()
{
	boo[0]=1;
	boo[1]=1;
	for(int i=2;i<=40;i++)
		for(int j=2;j<=40;j++)
			boo[i*j]=1;
}
void dfs(int now)
{
	if(now==n)
	{
		for(int i=0;i<n;i++)	printf("%d ",sto[i]);
		printf("\n");
		return;
	}
	//cout<<vis[6]<<endl;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			
			if(now==0||boo[i+sto[now-1]]==0)
			{
				if(now!=(n-1)||boo[i+sto[0]]==0)
				{
				//	cout<<now<<" "<<i<<endl;
					vis[i]=1;sto[now]=i;
					dfs(now+1);
					vis[i]=0;
				}
			}
		}
	}
}
int main()
{
	pt();
	cin>>n;
	sto[0]=1;vis[1]=1;
	dfs(1);
}
