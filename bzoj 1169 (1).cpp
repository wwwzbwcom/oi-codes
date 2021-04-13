#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int yn,xn,yc,xc;
int mat[50][50];
int sum[50][50];
int tmp[50]; 
int vis[50];
int dyp[50][50];
int ans=1e9;
int work()
{
	for(int i=0;i<50;i++)	for(int j=0;j<50;j++)	dyp[i][j]=1e9;
	for(int i=0;i<50;i++)	dyp[0][i]=0;
	for(int i=1;i<=yn;i++)
	{
		int las,cnt,val;
		memset(tmp,0,sizeof tmp);
		for(int j=i;j>=1;j--)
		{
			las=cnt=val=0;
			for(int k=1;k<=xn;k++)
				if(vis[k]==1)
				{
					tmp[cnt]+=sum[j][k]-sum[j][las];
					val=max(val,tmp[cnt]);
					las=k;
					cnt++;
				}
			if(j==1)	dyp[i][0]=min(dyp[i][0],val);
			for(int k=1;k<=min(i-1,yc);k++)	dyp[i][k]=min(dyp[i][k],max(val,dyp[j-1][k-1]));
		}
	}
	return dyp[yn][yc];
}
void dfs(int cur,int cnt)
{
	if(cnt==xc)
	{
		ans=min(ans,work());
		//for(int i=1;i<=xn;i++)	cout<<vis[i]<<"="; 
		//cout<<" "<<ans<<endl;
		return;
	}
	if(cur==xn)	return; 
	vis[cur]=1;	dfs(cur+1,cnt+1);	vis[cur]=0;
	dfs(cur+1,cnt);
}
void init()
{
	scanf("%d%d%d%d",&yn,&xn,&yc,&xc);
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
			scanf("%d",&mat[i][j]);
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
			sum[i][j]=sum[i][j-1]+mat[i][j];
}
int main()
{
	init();
	
	vis[xn]=1;
	dfs(1,0);
	
	printf("%d",ans); 
}
