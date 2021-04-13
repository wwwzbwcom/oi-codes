#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int g=0;
int fat[100000];
int boo[100000];
int find(int u)
{
	if(fat[u]==0)	return u;
	else	return fat[u]=find(fat[u]);
}
int main()
{
	while(cin>>n>>m,n,m)
	{
		memset(fat,0,sizeof fat);
		memset(boo,0,sizeof boo);
		for(int i=1;i<=m;i++)
		{
			int u,v;	cin>>u>>v;
			if(find(u)!=find(v))	fat[find(u)]=find(v);
		}
		int ans=0;
		for(int i=1;i<=n;i++)	if(boo[find(i)]==0)	boo[find(i)]=1,ans++;
		cout<<"Case "<<++g<<": "<<ans<<endl;
	}
}
