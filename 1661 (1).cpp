#include<iostream>
#include<map>
using namespace std;
const int oo=999999999;
int dp[100000];
int drop[100000][2][2];
int x1[100000],x2[100000],h[100000];
map <int,map<int,int> > book;
int gn,n,x,y,ma; 
int dfs(int u,int p)
{
	if(u==n+1) return 0;
	int ans=oo;
	if(dp[u]) return dp[u];
	if(drop[u][0][0])	ans=min(ans,dfs(drop[u][0][0],x1[u])+drop[u][0][1]+(p-x1[u]));
	else
	{
		int y=h[u];
		int t=0;
		y--,t++;
		while(book[y][x1[u]]==0) y--,t++;
		
		drop[u][0][0]=book[y][x1[u]];
		if(t<=ma)	drop[u][0][1]=t;
		else drop[u][0][1]=2*oo;
		
		ans=min(ans,dfs(drop[u][0][0],x1[u])+drop[u][0][1]+(p-x1[u]));
	}
	if(drop[u][1][0])	ans=min(ans,dfs(drop[u][1][0],x2[u])+drop[u][1][1]+(x2[u]-p));
	else
	{
		int y=h[u];
		int t=0;
		y--;t++;
		while(book[y][x2[u]]==0) y--,t++;
		
		drop[u][1][0]=book[y][x2[u]];
		if(t<=ma)	drop[u][1][1]=t;
		else drop[u][1][1]=2*oo;
		
		ans=min(ans,dfs(drop[u][1][0],x2[u])+drop[u][1][1]+(x2[u]-p));
	}
	cout<<u<<"="<<ans<<endl;
	return dp[u]=ans;                                                                              
}

int main()
{
	cin>>gn;
	cin>>n>>x>>y>>ma;
	for(int i=-20000;i<=20000;i++) book[0][i]=n+1;
	for(int i=1;i<=n;i++)
	{ 
		cin>>x1[i]>>x2[i]>>h[i];
		for(int j=x1[i];j<=x2[i];j++)	book[h[i]][j]=i;
	}
	int t=0;
	while(book[y][x]==0) y--,t++;
	if(t<=ma) cout<<dfs(book[y][x],x)+t;
	else cout<<-1<<endl;
}
