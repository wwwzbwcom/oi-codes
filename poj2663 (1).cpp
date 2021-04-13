#include<iostream>
#include<cstring>
using namespace std;
int in[10],out[10];
long long dp[100][100];
int main()
{
	int n;
	
	in[0]=0;	out[0]=1;
	in[1]=0;	out[1]=4;
	in[2]=0;	out[2]=7;
	in[3]=1;	out[3]=0;
	in[4]=4;	out[4]=0;
	in[5]=7;	out[5]=0;
	in[6]=3;	out[6]=4;
	in[7]=5;	out[7]=2;
	in[8]=6;	out[8]=1;
	in[9]=4;	out[9]=3;
	in[10]=2;	out[10]=5;
	in[11]=1;	out[11]=6;
	
//	memset(dp,0,sizeof dp);
	dp[0][0]=1;
	for(int i=0;i<=30;i++)
		for(int j=0;j<=7;j++)
			for(int k=0;k<=11;k++)
				if((j^in[k])==0)
					dp[i+1][out[k]]+=dp[i][j];
	while(cin>>n,n!=-1)
		cout<<dp[n][0]<<endl;
} 
