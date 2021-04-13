#include<iostream>
#include<cstdio>
using namespace std;
long long n;
long long w[1000100];
long long a[1000100];
long long b[1000100];
long long p[1000100];
long long vis[1000100];
long long mmni;
long long sum;
long long mni,cnt;
long long ans=0;
void dfs(long long u)
{
	vis[u]=1;
	sum+=w[a[u]];	mni=min(mni,w[a[u]]);	cnt++;
	long long v=p[a[u]];
	if(vis[v]==0)	dfs(v);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)	scanf("%lld",&w[i]),mmni=min(mmni,w[i]);
	for(int i=1;i<=n;i++)	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)	scanf("%lld",&b[i]),p[b[i]]=i; 
	for(int i=1;i<=n;i++)
		if(vis[i]==0)
		{
			sum=0;	mni=1e15;	cnt=0;
			dfs(i);
			ans+=min((sum-mni)+mni*(cnt-1),sum+(cnt+1)*mmni+mni);
		}
	printf("%lld\n",ans);
}
