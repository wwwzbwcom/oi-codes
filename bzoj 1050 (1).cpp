#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v,c;
	bool operator <(const Edge &in)const
	{
		return c<in.c;
	}
}e[5100];
int n,m;
int s,t;
int fat[5100];
double ans=1e15;
int a=0,b=0;
int find(int u)
{
	if(fat[u]==-1)	return u;
	else return	fat[u]=find(fat[u]);
}
int gcd(int a,int b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)	cin>>e[i].u>>e[i].v>>e[i].c;
	cin>>s>>t;
	sort(e,e+m);
	for(int i=0;i<m;i++)
	{ 
		memset(fat,-1,sizeof fat);
		for(int j=i;j<m;j++)
		{
			int u=e[j].u,v=e[j].v,c=e[j].c;
			if(find(u)!=find(v))	fat[find(u)]=find(v);
			if(find(s)==find(t))
			{
				if((double)c/((double)e[i].c)<ans)
				{
					ans=((double)c/(double)e[i].c);
					a=c;b=e[i].c;
				}
				break;
			}
		}
	}
	if(ans>1e14)	cout<<"IMPOSSIBLE"<<endl;
	else
	{
		int t=gcd(a,b);
		if(b/t==1)	cout<<a/t<<endl;
		else	cout<<a/t<<"/"<<b/t<<endl;
	}
}
