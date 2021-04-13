#include<iostream>
#include<cstring>
using namespace std;
const int mod=1000000007;
int gn;
int n,k;
int b[20];
int mul[20];
int dyp[20][100100];
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n>>k;
		for(int i=1;i<=k-1;i++)	cin>>b[i];
		memset(mul,0,sizeof mul);
		for(int i=1;i<=k-1;i++)
		{
			for(int j=i;j<=k-1;j++)
			{
				int tmp=1;
				for(int p=i;p<=j;p++)	tmp=((long long)tmp*b[p])%mod;
				//cout<<i<<" "<<j<<" "<<tmp<<endl;
				mul[i]+=tmp;	mul[i]%=mod;
			}
		} 
		for(int i=1;i<=k;i++)	mul[i]++;
		//for(int i=1;i<=k;i++)	cout<<i<<" "<<mul[i]<<endl;
		memset(dyp,0,sizeof dyp);
		dyp[0][0]=1;
		for(int i=1;i<=k;i++)
		{
			for(int j=0;j<=n;j++)	if(j-mul[i]>=0)	dyp[i][j]=(dyp[i-1][j-mul[i]]+dyp[i][j-mul[i]])%mod;
			if(i!=1)	for(int j=0;j<=n;j++)	dyp[i][j]=(dyp[i][j]+dyp[i-1][j])%mod;
		}
		cout<<dyp[k][n]<<endl;
	}
}
