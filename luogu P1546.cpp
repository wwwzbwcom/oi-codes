#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v,c;
	bool operator<(const Edge in)const
	{return c<in.c;	}
}e[20000];
int cnt=0;
int n;
int fa[200];
int find(int u)
{
	if(fa[u]==-1)	return u;
	return fa[u]=find(fa[u]);
}
int main()
{
	memset(fa,-1,sizeof fa);
	cin>>n;
	int c;
	for(int u=1;u<=n;u++)	for(int v=1;v<=n;v++)	cin>>c,	e[cnt].u=u,e[cnt].v=v,e[cnt].c=c,cnt++;
	sort(e,e+cnt);
	int ans=0;
	for(int i=0;i<cnt;i++)
	{
		int u=e[i].u,v=e[i].v,c=e[i].c;
		//cout<<find(u)<<"="<<find(v)<<"="<<c<<endl;
		if(find(u)!=find(v))
		{
		//	cout<<u<<"="<<v<<endl;
			fa[find(u)]=find(v);
			ans+=c;
		}
	}
	cout<<ans<<endl;
}
