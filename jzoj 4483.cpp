#include<iostream>
#include<cstdio>
using namespace std;
const int mod=1e9+7;
int n,m;
int a[20],b[20],c[20];
int vis[20];
int rev[200]; 
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=((long long)ans*ans)%mod;
		if(b%2==0)	return ans;
		else	return ((long long)ans*a)%mod;
	}
}
int getrev(int val)
{
	return qsm(val,mod-2);
}
int dfs(int p)
{
	int ans=0;
	if(p==n+1)
	{
		for(int i=1;i<=n;i++)	c[i]=c[i-1]+b[i];
		ans=m;
		for(int i=2;i<=n;i++)	ans=((long long)ans*rev[c[i]])%(long long)mod;
		return ans;
	}
	for(int i=1;i<=n;i++)	if(vis[i]==0)
	{
		vis[i]=1;
		b[p]=a[i];
		ans=(ans+dfs(p+1))%mod;
		vis[i]=0;
	}
	return ans;
}
int main()
{
	freopen("comb.in","r",stdin);
	freopen("comb.out","w",stdout);
	cin>>n;
	m=0;
	for(int i=1;i<=n;i++)	cin>>a[i],m+=a[i];
	int tmp=1;
	for(int i=1;i<=m;i++)	tmp=((long long)tmp*i)%mod;
	for(int i=1;i<=m;i++)	rev[i]=getrev(i); 
//	return 0;
	m=tmp;
	cout<<dfs(1)<<endl;
}
