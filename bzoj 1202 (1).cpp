#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct Node
{
	int l,r,v;
	bool operator<(const Node &in)const
	{
		return r<in.r;
	}
}no[1100];
int vis[200][200];
int dyp[200][200];
int main()
{
	int gn;scanf("%d",&gn);
	for(int g=0;g<gn;g++)
	{
		int flag=0;
		memset(vis,0,sizeof vis);
		memset(dyp,0,sizeof dyp);
		vis[0][0]=1;
		int n,m;scanf("%d%d",&n,&m);
		
		for(int i=0;i<m;i++)	scanf("%d%d%d",&no[i].l,&no[i].r,&no[i].v);
		sort(no,no+m);
		
		for(int i=0;i<m;i++)
		{
			int l=no[i].l,r=no[i].r,v=no[i].v;
			vis[l][r]=1;	dyp[l][r]=v;
			for(int j=0;j<=l-1;j++)
			{
				if(vis[j][l-1]!=0)
				{
					if(vis[j][r]==1)
					{
						if(dyp[j][r]!=dyp[j][l-1]+v)	flag=1;
					}
					else
					{
						vis[j][r]=1;
						dyp[j][r]=dyp[j][l-1]+v;
					}
				}
			}
		}
		if(flag==1)	printf("false\n");
		else	printf("true\n");d
	}
}
