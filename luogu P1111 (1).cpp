#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v,t;
	bool operator<(const Edge in)const{return t<in.t;}
}e[200000];
int n,m;
int fa[200000];
int find(int u)
{
	if(fa[u]==-1)	return u;
	else	return fa[u]=find(fa[u]);
}
int main()
{
	memset(fa,-1,sizeof fa);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)	cin>>e[i].u>>e[i].v>>e[i].t;
	sort(e+1,e+m+1);
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		if(find(e[i].u)!=find(e[i].v))
		{
		//	cout<<i<<" "<<e[i].u<<" "<<e[i].v<<endl;
			ans=e[i].t;
			fa[find(e[i].u)]=find(e[i].v);
	
			int flag=0;
			for(int j=2;j<=n;j++)	if(find(j)!=find(1))	{flag=1;break;}
			if(flag==0)	break;
		}
	}
	int flag=0;
	for(int j=2;j<=n;j++)	if(find(j)!=find(1))	{flag=1;break;}
	if(flag==0)	cout<<ans<<endl;
	else	cout<<-1<<endl;	
}
