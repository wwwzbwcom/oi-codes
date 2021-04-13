#include<iostream>
#include<cstring>
using namespace std;
struct bigNum
{
	int s[100];
	int len;
	bigNum(){len=1;memset(s,0,sizeof s);}
	void init()
	{
		len=1;
		memset(s,0,sizeof s);
	}
	void output()const
	{
		for(int i=len-1;i>=0;i--)	cout<<s[i];
	}
	bool operator<(const bigNum &in)const
	{
		if(len!=in.len)	return len<in.len;
		for(int i=len-1;i>=0;i--)
			if(s[i]!=in.s[i])	return s[i]<in.s[i];
	}
	bigNum operator+(const bigNum &in)const
	{
		bigNum ans;
		ans.len=max(in.len,len);
		int carry=0;
		for(int i=0;i<ans.len;i++)
		{
			ans.s[i]=in.s[i]+s[i]+carry;
			if(ans.s[i]>=10)	carry=1,ans.s[i]-=10;
			else	carry=0;
		}
		if(carry)	ans.s[ans.len++]=1;
		return ans;
	}
	bigNum operator*(const int &in)const
	{
		bigNum ans;
		ans.len=len;
		int carry=0;
		for(int i=0;i<ans.len;i++)
		{
			ans.s[i]=in*s[i]+carry;
			carry=ans.s[i]/10;
			ans.s[i]%=10;
		}
		//cout<<carry<<endl;
		while(carry)
		{
			ans.s[ans.len++]=carry%10;
			carry/=10;
		}
		return ans;
	}
	
};
int n,m;
bigNum two[100];
int s[100];
bigNum dp[100][100];
bool vis[100][100];
void dfs(int l,int r)
{
	if(l>r)	return;
	if(vis[l][r])	return;
	vis[l][r]=1;
	dfs(l+1,r);
	dfs(l,r-1);
	dp[l][r]=max(dp[l][r],dp[l+1][r]+two[(l-1)+(m-r)+1]*s[l]);
	dp[l][r]=max(dp[l][r],dp[l][r-1]+two[(l-1)+(m-r)+1]*s[r]);
}
int main()
{
//	for(int i=0;i<100;i++)	two[i].init();
//	cout<<(two[0]*1).len<<endl;
	two[0].s[0]=1;
	for(int i=1;i<100;i++)	two[i]=two[i-1]*2;
//	(two[10]+two[9]).output();
	cin>>n>>m;
	bigNum ans;
	ans.init();
	for(int i=1;i<=n;i++)
	{
		for(int i=0;i<100;i++)	for(int j=0;j<100;j++)	dp[i][j].init();
		memset(vis,0,sizeof vis);
		for(int j=1;j<=m;j++)	cin>>s[j];
		dfs(1,m);
	//	dp[1][m].output();cout<<endl;
		ans=ans+dp[1][m];
	}
	ans.output();
}
