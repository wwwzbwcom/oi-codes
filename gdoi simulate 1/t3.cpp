#include<iostream>
using namespace std;
const int mod=1000000003;
const int maxn=2000;
int n,m;
int ind[maxn];
int cnt;
int ans;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		ind[u]++;	ind[v]++;
	}
	for(int i=1;i<=n;i++)	if(ind[i]==1)	cnt++;
	ans=1;
	for(int i=1;i<=cnt;i++)	ans*=i;
	cout<<ans-1<<endl;
}
