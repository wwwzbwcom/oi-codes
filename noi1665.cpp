#include<iostream>
using namespace std;
//int in[10] ={000,100,000,001, 100,101,110,111, 010,011,001,000};
//int out[10]={100,000,001,000, 011,010,001,000, 101,100,110,111};
int in[] ={0,4,0,1, 4,5,6,7,2,3,1,0};
int out[]={4,0,1,0, 3,2,1,0,5,4,6,7};
int dp[100][10];
int main()
{
	dp[0][0]=1;
	for(int i=0;i<=30;i++)
	{
		for(int j=0;j<8;j++)
			for(int k=0;k<12;k++)
				if(in[k]==j)
					dp[i+1][out[k]]+=dp[i][j];
	}
//	cout<<dp[2][0]<<endl;
//	cout<<dp[8][0]<<endl;
//	cout<<dp[12][0]<<endl;
	int n;
	while(cin>>n)
	{
		if(n==-1)	break;
		cout<<dp[n][0]<<endl;
	}
	return 0;	
}
