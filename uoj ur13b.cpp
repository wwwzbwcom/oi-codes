#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1100;
int n;
int a[maxn],b[maxn];
int dyp[maxn][maxn];	//place(base on thing)	combo
int main()
{
//	freopen("ex_data3.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i]>>b[i];
	int ans=0;
	memset(dyp,-1,sizeof dyp);
	for(int i=1;i<=n;i++)	dyp[i][1]=0;
	for(int i=n;i>=1;i--)
		for(int j=i+1;j<=n;j++)
			if(abs(a[j]-a[i])<=b[j]-b[i])
			{
			//	cout<<i<<" "<<j<<endl;
				if(j==i+1)
				{
					for(int k=1;k<=(n-j+1);k++)	if(dyp[j][k]!=-1)
						dyp[i][k+1]=max(dyp[i][k+1],dyp[j][k]);
				}
				else
				{
					for(int k=1;k<=(n-j+1);k++)	if(dyp[j][k]!=-1)	
						dyp[i][1]=max(dyp[i][1],dyp[j][k]+(k*k));
				} 
			}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(dyp[i][j]!=-1)
				ans=max(ans,dyp[i][j]+j*j);
		//	cout<<dyp[i][j]<<" ";
		}
	//	cout<<endl;
	}
	cout<<ans<<endl;
}
