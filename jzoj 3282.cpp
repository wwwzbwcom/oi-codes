#include<algorithm>
//#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int gn;
double pro[10];
double dyp[100];
class Matrix
{
	public:
		int y,x;
		double m[10][10];
		void init()
		{
			y=x=0;
			memset(m,0,sizeof m);
		}
		/*
		void debug()
		{
			cout<<y<<"==="<<x<<endl;
			for(int i=0;i<y;i++)
			{
				for(int j=0;j<x;j++)
					cout<<m[i][j]<<"	";
				cout<<endl;
			}
		}
		*/
		void guass()
		{
			//debug();
			for(int k=0;k<y;k++)
			{
				int p=k;
				for(int i=k+1;i<y;i++)	if(abs(m[i][k])>abs(m[p][k]))	p=i;
				if(p!=k)	swap(m[k],m[p]);
				
				double tmp=m[k][k];
				for(int i=0;i<x;i++)	m[k][i]/=tmp;
				for(int i=0;i<y;i++)	if(i!=k)
				{
					tmp=m[i][k]/m[k][k];
					for(int j=0;j<x;j++)	m[i][j]-=tmp*m[k][j];
				}
			}
			//debug();
			for(int i=0;i<x;i++)	dyp[51+i]=m[i][x-1];
		}
}ma;
class Graph
{
	private:
		class Edge
		{
			public:
				int v,nxt;
				double c;
		}e[100*100];
		int pre[100],en;
	public:
		void init()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v,double c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		}
		void work()
		{
			for(int u=50;u>=0;u--)
			{
				double ans=0;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;	double c=e[i].c;
					ans+=dyp[v]*c;
				}
				dyp[u]=ans+1;
			}
		//	for(int u=1;u<=56;u++)	printf("%d %.10lf\n",u,dyp[u]);
		}
}gr;
void init()
{
	for(int i=0;i<100;i++)	dyp[100]=1e100;
	dyp[56]=0;
}
int main()
{
	freopen("flying2.in","r",stdin);
	scanf("%d",&gn);
	while(gn--)
	{
		init();
		ma.init();
		gr.init();
		for(int i=1;i<=6;i++)	scanf("%lf",&pro[i]);
		for(int i=0;i<=50;i++)
		{
			int u=i;
			for(int j=1;j<=6;j++)
			{
				int v=i+j;
				if(v%4==2&&v<=46)
				{
					if(v==18)	gr.addedge(u,34,pro[j]);
					else
					{
						if(v==14)	gr.addedge(u,30,pro[j]);
						else	gr.addedge(u,v+4,pro[j]);
					}
				}
				else	gr.addedge(u,v,pro[j]);
			}
		}
		ma.y=6;	ma.x=7;
		for(int i=51;i<=55;i++)
		{
			ma.m[i-51][i-51]=1,ma.m[i-51][6]=1;
			for(int j=1;j<=6;j++)
			{
				int u=i,v=i+j;
				if(v>56)	v=56-(v-56);
				ma.m[u-51][v-51]+=-pro[j];
			}
		}
		ma.m[5][5]=1,ma.m[5][6]=0;
		ma.guass();
		gr.work();
		double ans=dyp[0]+(1/pro[6]);
		if(ans!=ans||ans>=1e100||ans<0)	printf("T_T\n");
		else	printf("%.8lf\n",dyp[0]+(1/pro[6]));
	}
}
