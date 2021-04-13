#include<iostream>
using namespace std;
int n;
int sto[150][150];
int tmp[150][150];
int sum[150][150];
int ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>sto[i][j],tmp[i][j]=sto[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			tmp[i][j]+=tmp[i][j-1]; 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]=sum[i-1][j]+tmp[i][j];
	for(int y1=1;y1<=n;y1++)
		for(int x1=1;x1<=n;x1++)
			for(int y2=y1;y2<=n;y2++)
				for(int x2=x1;x2<=n;x2++)
				{
					ans=max(ans,sum[y2][x2]-sum[y2][x1-1]-sum[y1-1][x2]+sum[y1-1][x1-1]);
				}
	cout<<ans<<endl;
}
