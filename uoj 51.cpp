#include<cstdio>
using namespace std;
int n,m;
int vis[40000][40];
int dyp[40000][40];
int dfs(int a,int b)
{
	if(vis[a][b])	return dyp[a][b];
	
	vis[a][b]=1;
//	cout<<dfs(a,b+1)<<" "<<dfs(a+1,b)<<endl;
	if(dfs(a,b+1)&&dfs(a+1,b))	dyp[a][b]=0;
	else	dyp[a][b]=1;
	
	return dyp[a][b];
}
int main()
{
//	freopen("ex_data2.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=2;i<40000;i++)
	{
		long long cur=1,flag=0;
		for(int j=1;j<40;j++)
		{
			if(flag==0)	cur*=i;
			if(cur>n||flag)
			{
				flag=1;
				vis[i][j]=1;
				dyp[i][j]=1;
			}
		}
	}
	for(int i=2;i<40000;i++)
		if(i<=n&&i*i>n)
		{
			vis[i][1]=1;
			if((n-i)%2)	dyp[i][1]=0;
			else		dyp[i][0]=1;
			dyp[i][1]=0;
		}
	for(int i=1;i<=m;i++)
	{
		int a,b;	scanf("%d%d",&a,&b);
		if((long long)a*a>n)
		{
			if((n-a)%2)	printf("Yes\n");
			else		printf("No\n");
		}
		else
		{
			if(dfs(a,b))	printf("Yes\n");
			else			printf("No\n");
		}
	}
}
