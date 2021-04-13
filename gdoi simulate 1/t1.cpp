#include<iostream>
using namespace std;
const long long mod=1e9+7;
int n,m,r,c,s;
long long ans=0;
long long C[4000][4000];
void init()
{
	C[0][0]=1;
	for(int i=1;i<4000;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)	C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int main()
{
	init();
//	cout<<C[5][2]<<endl; 
	cin>>n>>m>>r>>c>>s;
	for(int i=0;i<=r;i++)	if((r-i)%2==0)	
		for(int j=0;j<=c;j++)	if(i*m+j*(n-2*i)==s&&(c-j)%2==0)
		{
			long long cur=(C[n][i]*C[m][j])%mod;
			cout<<cur<<endl;
			if(n-1>=0)	cur=(cur*C[n+(r-i)/2-1][n-1])%mod;
			cout<<cur<<endl;
			if(m-1>=0)	cur=(cur*C[m+(c-j)/2-1][m-1])%mod;
			cout<<i<<" "<<j<<" "<<cur<<endl;
			ans=(ans+cur)%mod;
		}
	cout<<ans;
}
