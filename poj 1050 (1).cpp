#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=1010;

char a[maxn],b[maxn];
int len;

int dp[maxn][maxn];
int ap[maxn][maxn],bp[maxn][maxn];
int af[maxn][maxn];
int bf[maxn][maxn];

char ans[3*maxn];
int cnt;
int main()
{
	while(~scanf("%s",a+1))
	{
		len=strlen(a+1);
		memset(dp,0,sizeof dp);
		memset(ap,0,sizeof ap);
		memset(bp,0,sizeof bp);
		memset(af,0,sizeof af);
		memset(bf,0,sizeof bf);
		
		for(int i=1;i<=len;i++)	b[i]=a[len-i+1];
	//	cout<<b+1<<endl;
		
		for(int i=1;i<=len;i++)
		{
			for(int j=1;j<=len;j++)
			{
				if(dp[i-1][j]<=dp[i][j-1])	dp[i][j]=dp[i][j-1],ap[i][j]=ap[i][j-1],bp[i][j]=bp[i][j-1];
				else	dp[i][j]=dp[i-1][j],ap[i][j]=ap[i-1][j],bp[i][j]=bp[i-1][j];
				
				if(a[i]==b[j])	dp[i][j]=dp[i-1][j-1]+1,ap[i][j]=i,bp[i][j]=j,af[i][j]=ap[i-1][j-1],bf[i][j]=bp[i-1][j-1];//,cout<<i<<" "<<j<<" "<<ap[i-1][j-1]<<endl;
			//	cout<<ap[i][j]<<"="<<bp[i][j]<<"	";
			}
		//	cout<<endl;
		}
		int ac=ap[len][len],bc=bp[len][len];
		int al=len,bl=len;
		cnt=0;
		while(1)
		{
		//	cout<<al<<"="<<ac<<" "<<bl<<"="<<bc<<endl;
		
			for(int i=al;i>ac;i--)	ans[cnt++]=a[i];
			for(int i=bl;i>bc;i--)	ans[cnt++]=b[i];
			if(ac==0&&bc==0)break;
			ans[cnt++]=a[ac];
		//	cout<<a[ac]<<"="<<ac<<" "<<b[bc]<<"="<<bc<<endl;
			al=ac-1;	bl=bc-1;
			int at,bt;
			at=ap[ac-1][bc-1];	bt=bp[ac-1][bc-1];
			ac=at,bc=bt;
		}
	//	cout<<endl;
		cout<<cnt<<endl;
		for(int i=0;i<cnt/2;i++)
		{
		//	cout<<cnt-i-1<<" "<<i<<" "<<ans[i]<<endl;
			ans[cnt-i-1]=ans[i];
		}
		for(int i=0;i<cnt;i++)	if(ans[i]!=ans[cnt-i-1])	while(1);
		
		printf("%d ",len-dp[len][len]);
		for(int i=0;i<cnt;i++)	putchar(ans[i]);
		putchar('\n');
	}
}
