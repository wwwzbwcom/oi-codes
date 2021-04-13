#include<iostream>
using namespace std;
int n,m;
int ope[1000];
int clo[1000];
int dp[10000];
void output(int n)
{
	if(n!=0)
	{
		output(n/2);
		cout<<n%2;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		ope[i]=0;
		clo[i]=(1<<n)-1;
		for(int j=0;j<n;j++)
		{
			int t;	cin>>t;
			if(t==1)	ope[i]+=(1<<j);
			if(t==-1)	clo[i]-=(1<<j);
		}
	//	output(ope[i]);cout<<endl;
	//	output(clo[i]);cout<<endl;
	//	cout<<"=============="<<endl;
	}
	for(int i=0;i<10000;i++)	dp[i]=1e9;
	dp[0]=0;
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<m;j++)
			dp[(i|ope[j])&clo[j]]=min(dp[(i|ope[j])&clo[j]],dp[i]+1);
	if(dp[(1<<n)-1]==1e9)	cout<<-1<<endl;
	else	cout<<dp[(1<<n)-1]<<endl;
}
