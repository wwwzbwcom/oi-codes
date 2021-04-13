#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
int n,m;
int a[1000],b[1000];
int dp[210][25][1000];
int pre[210][25][1000];
int g=0;
void output()
{
	//cout<<dp[3][2][502]<<endl;
	int ans=2e9,max0=-1;
	for(int i=50;i<=950;i++)	if(dp[n][m][i]!=-1)	if(abs(i-500)<abs(ans-500) || (abs(i-500)==abs(ans-500)&&max0<dp[n][m][i]) )	ans=i,max0=dp[n][m][i];
	//cout<<ans<<" "<<max0<<" "<<dp[n][m][502]<<endl; 
	int i=n,j=m,k=ans;	stack <int> s;
	int aa=0,ba=0;
//	int temp;
	int now;
	while(1)
	{
		now=pre[i][j][k];
		if(now==-1)	break;
		//cout<<now<<endl;
		aa+=a[now];ba+=b[now];
		s.push(now);
		i=now-1;j--;k+=-a[now]+b[now];
	}
	
	cout<<"Jury #"<<++g<<endl;
	cout<<"Best jury has value "<<aa<<" for prosecution and value "<<ba<<" for defence:"<<endl; 
	while(!s.empty())
	{
		cout<<" "<<s.top();
		s.pop();
	}
	cout<<endl;
}
int main()
{
	while(cin>>n>>m,n,m)
	{
		memset(dp,-1,sizeof dp);
		memset(pre,-1,sizeof pre);
		
		for(int i=1;i<=n;i++)	cin>>a[i]>>b[i];
		
		
		int flag=0;
		dp[0][0][500]=0;
		for(int i=1;i<=n;i++)
		{
			dp[i][0][500]=0;
			for(int j=m;j>=1;j--)
			{
				for(int k=100;k<=900;k++)
				{
					if(dp[i-1][j][k]>dp[i][j][k])	dp[i][j][k]=dp[i-1][j][k],pre[i][j][k]=pre[i-1][j][k];
				//	dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k];pre[i][j][k]=pre[i-1][j][k];
					if(dp[i-1][j-1][k]!=-1)
					{
						if(dp[i][j][k+a[i]-b[i]]<dp[i-1][j-1][k]+a[i]+b[i])
						{
							dp[i][j][k+a[i]-b[i]]=dp[i-1][j-1][k]+a[i]+b[i];
							pre[i][j][k+a[i]-b[i]]=i;
							//if(i==3)	cout<<i<<" "<<j<<" "<<k<<" "<<k+a[i]-b[i]<<" "<<dp[3][2][502]<<endl;
							
						}
					}
					//if(i>=3)getchar();
				}
			//	cout<<dp[3][2][502]<<endl;
			}
			
		}
		
	//	if(flag==0)	while(1);
		output();
	}
}
