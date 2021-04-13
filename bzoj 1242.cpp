#include<cstdio>
//#include<iostream>
using namespace std;
const int maxn=1100;
int edg[maxn][maxn];
int n,m;
int deg[maxn];
int sto[maxn];
int mar[maxn];
int ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		edg[u][v]=edg[v][u]=1;
	}
	deg[0]=-1;
	for(int i=n;i>=1;i--)
	{
		int u=0;
		for(int j=1;j<=n;j++)	if(deg[j]>deg[u]&&mar[j]==0)	u=j;
		sto[i]=u;	mar[u]=1;
		for(int j=1;j<=n;j++)	if(edg[u][j])	deg[j]++;
	}
	ans=1;
//	for(int i=1;i<=n;i++)	cout<<" "<<sto[i]<<endl;
	for(int i=1;i<=n;i++)
	{
		int u=sto[i],f=0,v;
		for(int j=1;j<=n;j++)
			if(edg[u][sto[j]]&&mar[sto[j]])
			{
				if(f==0)	v=sto[j],f=1;
				else	if(f&&edg[v][sto[j]]==0)
				{
				//	cout<<u<<" "<<v<<" "<<j<<endl;
					ans=0;
					break;
				}
			}
		mar[u]=0;
	}
	if(ans==1)	printf("Perfect\n");
	else	printf("Imperfect\n");
}
