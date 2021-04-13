#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int a[500],b[500];
int dp[500][500];
int pre[500][500];
int aa,ba;
int calc(int j,int k)
{
	int now=pre[j][k];
	cout<<now<<endl;
	if(j-1>0)	calc(j-1,k-a[now]+b[now]);
	aa+=a[now],ba+=b[now];
}
void output(int j,int k)
{
	int now=pre[j][k];
	if(j-1>0)	output(j-1,k-a[now]+b[now]);
	cout<<" "<<now;
}
int main()
{
	int n,m;
	int g=0;
	while(cin>>n>>m,n,m)
	{
		memset(dp,-1,sizeof dp);
		aa=0;ba=0;
		for(int i=1;i<=n;i++)	cin>>a[i]>>b[i];
	 
	 	dp[0][250]=0;
		for(int i=1;i<=n;i++)
		{
		//	cout<<"=============="<<endl;
			for(int j=m-1;j>=0;j--)
				for(int k=50;k<=450;k++)
					if(dp[j][k]+a[i]+b[i]>dp[j+1][k+a[i]-b[i]]&&dp[j][k]!=-1)
					//	cout<<j<<" "<<k<<endl,
						dp[j+1][k+a[i]-b[i]]=dp[j][k]+a[i]+b[i],pre[j+1][k+a[i]-b[i]]=i;
		}
		int ans=2e9;
		for(int i=50;i<=450;i++)	if(dp[m][i]!=-1)	if(abs(i-250)<abs(ans-250))	ans=i;
		cout<<pre[m][ans]<<" "<<pre[m-1][ans-a[pre[m][ans]]+b[pre[m][ans]]]<<endl;
		cout<<"Jury #"<<++g<<endl;
		calc(m,ans);
		cout<<"Best jury has value "<<aa<<" for prosecution and value "<<ba<<" for defence:"<<endl; 
		output(m,ans);
		cout<<endl;
	}
}
