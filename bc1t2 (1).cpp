#include<cstdio>
#include<map>
using namespace std;
map <long long,long long> dp;
const int oo=999999999;
int gn;
int n,m;
int map0[20][20];
int vis[20];
template<class T> 
inline void read(T& x)
{
	char c = getchar(); T p = 1, n = 0;
	while(c < '0' || c > '9'){if(c == '-') p = -1; c = getchar();}
	while(c >= '0' && c <= '9'){n = n * 10 + c - '0'; c = getchar();}
	x = p * n;
}
template<class T>
inline void read(T& x, T& y){read(x), read(y);}
template<class T>
inline void read(T& x, T& y, T& z){read(x), read(y), read(z);}
int dfs(int u,int fee,int cnt)
{
	int cur=0,mu=1;
	for(int i=1;i<=n;i++) cur+=vis[i]*mu,mu*=10;
	if(dp.find(cur)!=dp.end()) return dp[cur];
	if(cnt==n) return fee+map0[u][1];
	int ans=oo;
	for(int v=1;v<=n;v++)
	{
		if(map0[u][v]!=oo&&vis[v]==0)
		{
			vis[v]=1;
			int temp=dfs(v,fee+map0[u][v],cnt+1);
			if(temp<ans) ans=temp;
			vis[v]=0;
		}
	}
	return dp[cur]=ans;
}
int main()
{
	scanf("%d",&gn);
	while(gn--)
	{
		scanf("%d%d",&n,&m);
		
		for(int i=0;i<20;i++) vis[i]=0;
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
				map0[i][j]=oo;
				
		for(int i=1;i<=m;i++)
		{
			int u,v,c;
			read(u,v,c);
			if(c<map0[u][v])
			map0[u][v]=map0[v][u]=c;
		}
		for(int i=1;i<=n;i++) map0[i][i]=0;
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					if(map0[i][k]+map0[k][j]<map0[i][j])
						map0[i][j]=map0[i][k]+map0[k][j];
		vis[1]=1;
		printf("%d\n",dfs(1,0,1));
	}
}
