#include<iostream>
using namespace std;
const int oo=999999999;
int vis[200];
int low[200];
int map[200][200];
int pre[200];
int output[200][2];
int n,cnt=0;
int prim()
{
	vis[1]=1;
	int ans=0;
	for(int i=1;i<=n;i++) low[i]=map[1][i],pre[i]=1;
	for(int i=1;i<n;i++)
	{
		int uv=oo,v;
		for(int j=1;j<=n;j++) if(vis[j]==0&&uv>low[j]) uv=low[j],v=j;
		vis[v]=1;
		if(uv>0)
		{
			output[cnt][0]=pre[v];output[cnt][1]=v;
			if(output[cnt][0]>output[cnt][1]) swap(output[cnt][0],output[cnt][1]);
			cnt++;
		}
		ans+=uv;
		for(int j=1;j<=n;j++) if(vis[j]==0&&map[v][j]<low[j]) low[j]=map[v][j],pre[j]=v;
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>map[i][j];
	int ans=prim();
	cout<<cnt<<endl;
	for(int i=0;i<cnt;i++)
		cout<<output[i][0]<<" "<<output[i][1]<<endl;
	cout<<ans;
}
