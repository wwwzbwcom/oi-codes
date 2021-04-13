#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
const int maxn=1000100;
int n;
int us[maxn],vs[maxn];
int ind[maxn];
int poi[maxn];
vector <int> edv[maxn],opp[maxn];
vector <int> vis[maxn],cnt[maxn],sum[maxn];
int mxa=0,p;
void dfs(int u,int f)
{
	if(vis[u][f]==1)	return;
	vis[u][f]=1;
	for(int i=0;i<edv[u].size();i++)
	{
		if(i!=f)
		{
			dfs(edv[u][i],opp[u][i]);
			cnt[u][f]+=cnt[edv[u][i]][opp[u][i]];
			sum[u][f]+=sum[edv[u][i]][opp[u][i]];
		}
	}
	sum[u][f]+=cnt[u][f];
	cnt[u][f]++;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&us[i],&vs[i]);
		ind[us[i]]++;	ind[vs[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		edv[i].resize(ind[i],0);
		opp[i].resize(ind[i],0);
		vis[i].resize(ind[i],0);
		cnt[i].resize(ind[i],0);
		sum[i].resize(ind[i],0);
	}
	for(int i=1;i<=n-1;i++)
	{
		int u=us[i],v=vs[i];
		edv[u][poi[u]]=v;	opp[u][poi[u]]=poi[v];
		edv[v][poi[v]]=u;	opp[v][poi[v]]=poi[u];
		poi[u]++;	poi[v]++;
	}
	
	for(int u=1;u<=n;u++)
		for(int i=0;i<edv[u].size();i++)
			dfs(u,i);
			
	for(int u=1;u<=n;u++)
	{
		int ccn=0,csu=0;
		for(int i=0;i<edv[u].size();i++)
			ccn+=cnt[edv[u][i]][opp[u][i]],csu+=sum[edv[u][i]][opp[u][i]];
		csu+=ccn;
		printf("%d %d\n",u,csu);
		if(mxa<csu)	mxa=csu,p=u;
	}
	printf("%d\n",p);
}
