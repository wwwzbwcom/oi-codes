#include<algorithm> 
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m;
int deg[600];
class Matrix
{
	public:
		double m[600][600];
		double ans[600];
		int y,x;
		void debug()
		{
			for(int i=0;i<y;i++)
			{
				for(int j=0;j<x;j++)
					cout<<m[i][j]<<" "; 
				cout<<endl;
			}
		}
		void guass()
		{
			for(int k=0;k<y;k++)
			{
				int p=k;
				for(int i=0;i<y;i++)	if(m[i][k]>m[p][k])	p=i;
				if(p!=k)	swap(m[p],m[k]);
				
				double tmp=m[k][k];
				for(int i=0;i<x;i++)	m[k][i]/=tmp;
				for(int i=0;i<y;i++)	if(i!=k)
				{
					double tmp=m[i][k]/m[k][k];
					for(int j=0;j<x;j++)	m[i][j]-=tmp*m[k][j];
				}
			}
			for(int i=0;i<y;i++)	ans[i]=m[i][x-1]; 
		}	
}ma;
class Work
{
	public:
		class Edge
		{
			public:
				int v,nxt;
		}e[600*600*2];
		int pre[600],en;
		double ans[600*600];
		Work()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++; 
		}
		double work()
		{
			for(int u=1;u<=n;u++)
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					if(u!=n)	ans[i/2]+=ma.ans[u-1]/deg[u];
				}
			sort(ans,ans+m);
			double sum=0;
			for(int i=0;i<m;i++)	sum+=ans[i]*(m-i);
			return sum;
		} 
}wk;
int main()
{
	cin>>n>>m;
	ma.y=n;	ma.x=n+1;
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;	deg[u]++;	deg[v]++;
		wk.addedge(u,v);
	}
	ma.m[0][n]=1;
	for(int i=0;i<n;i++)	ma.m[i][i]++;
	for(int u=1;u<=n;u++)
		for(int i=wk.pre[u];i!=-1;i=wk.e[i].nxt)
		{
			int v=wk.e[i].v;
			if(u!=n)	ma.m[v-1][u-1]-=(1.0/deg[u]);
		}
	ma.guass();
	printf("%.3lf",wk.work());
}
