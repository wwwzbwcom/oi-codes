#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=5010;
int x0,a,b,c,d;
int n,m,q;
int val[maxn*maxn];
int map[maxn][maxn];
int lef[maxn],rig[maxn];
int rnd()
{
	x0=((long long)a*x0*x0%d+(long long)b*x0%d+(long long)c)%d;
	if(x0<0)	cout<<x0<<"============="<<endl;
	return x0;
}
void erase(int y,int x)
{
//	cout<<y<<" "<<x<<endl;

	for(int i=1;i<=y-1;i++)	rig[i]=min(rig[i],x);
	for(int i=y+1;i<=n;i++)	lef[i]=max(lef[i],x);
}
int main()
{
	cout<<((int)1e9+(int)1e9+(int)1e9)<<endl; 
	scanf("%d%d%d%d%d",&x0,&a,&b,&c,&d);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)	lef[i]=1,rig[i]=m;
	for(int i=1;i<=n*m;i++)	val[i]=i;
	for(int i=1;i<=n*m;i++)	swap(val[i],val[rnd()%i+1]);
	for(int i=1;i<=q;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		swap(val[u],val[v]);
	}
//	for(int i=1;i<=n*m;i++)	cout<<i<<" "<<val[i]<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			map[i][j]=val[(i-1)*m+(j-1)+1];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			val[map[i][j]]=(i-1)*m+(j-1);

	for(int i=1;i<=n*m;i++)
	{
		int y=val[i]/m+1,x=val[i]%m+1;
		if(lef[y]<=x&&x<=rig[y])
		{
			printf("%d ",i);
			erase(y,x);
		}
	}
}
