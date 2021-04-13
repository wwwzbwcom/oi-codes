#include<algorithm>
#include<cstdio>
using namespace std;
int n;
int t1,t2,t3;
int f[30100],g[30100];
int ans=1e9;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<30100;i++)	f[i]=1e9,g[i]=1e9;
	f[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&t1,&t2,&t3);
		for(int i=0;i<=30000;i++)
		{
			if(t1)	g[i+t1]=min(g[i+t1],f[i]);
			if(t2)	g[i]=min(g[i],f[i]+t2);
			if(t3)	g[i+t3]=min(g[i+t3],f[i]+t3);
		}
		for(int i=0;i<=30000;i++)	f[i]=g[i],g[i]=1e9;
	}
	for(int i=0;i<=30000;i++)	ans=min(ans,max(i,f[i]));
	printf("%d",ans);
}
