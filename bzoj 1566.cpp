#include<iostream>
#include<cstring>
using namespace std;
const int maxn=510;
const int mod=1024523;
int dyp[maxn][maxn][maxn];
char a[maxn],b[maxn];
int n,m;
int dfs(int a1,int b1,int a2)
{
	if(dyp[a1][b1][a2]!=-1)	return dyp[a1][b1][a2];
	
	if(a1==n&&b1==m)	return dyp[a1][b1][a2]=1;
	
	int b2=(a1+b1)-a2;
	dyp[a1][b1][a2]=0;
	if(a1<n&&a2<n&&a[a1]==a[a2])	dyp[a1][b1][a2]+=dfs(a1+1,b1  ,a2+1);
	if(a1<n&&b2<m&&a[a1]==b[b2])	dyp[a1][b1][a2]+=dfs(a1+1,b1  ,a2  );
	if(b1<m&&a2<n&&b[b1]==a[a2])	dyp[a1][b1][a2]+=dfs(a1  ,b1+1,a2+1);
	if(b1<m&&b2<m&&b[b1]==b[b2])	dyp[a1][b1][a2]+=dfs(a1  ,b1+1,a2  );
	
	dyp[a1][b1][a2]%=mod;
	
	return dyp[a1][b1][a2];
}
int main()
{
	memset(dyp,-1,sizeof dyp);
	scanf("%d%d",&n,&m);
	scanf("%s%s",a,b);
	printf("%d",dfs(0,0,0));
}
