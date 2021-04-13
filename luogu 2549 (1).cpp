#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=1010;

char s[] = "OIZEhSqLBG";

char hs[256];

void init()
{
	for(int i=0;i<=9;i++) hs[s[i]] = i+'0';
	hs['D'] = '0';
}

int d,n;

string key[10001];
int len[10100];
int dp[10100][250];
void convert(string &s)
{
	 int len = s.length();
	 for(int i=0;i<len;i++) s[i]  = hs[s[i]];
}

bool cmp(string a,string b)
{
	return (a+b)<(b+a);
}

int flag=0;
void dfs(int now,int cur)
{
	if(cur==0)	return;
	if(dp[now-1][cur-len[now]])
	{
		if(flag==0&&key[now][0]=='0')
		{
			cout<<key[now][0]<<".";
			for(int i=1;i<len[now];i++)	cout<<key[now][i];
		}
		else	cout<<key[now];
		flag=1;
		dfs(now-1,cur-len[now]);
	}
	else	dfs(now-1,cur);
}

int main()
{
	init();
	 while(scanf("%d%d",&d,&n)!=EOF)
	 {
		for(int i=1;i<=n;i++) cin>>key[i],convert(key[i]);
		for(int i=1;i<=n;i++)	reverse(key[i].begin(),key[i].end());
		sort(key+1,key+n+1,cmp);
		
		for(int i=1;i<=n;i++)	len[i]=key[i].size();
		
		for(int i=1;i<=d;i++) dp[0][i]=0;
		dp[0][0] = 1;
		for(int i=1;i<=n;i++)
		{
			dp[i][0]=1;
			for(int j=1;j<=d;j++)
			{
				dp[i][j] = dp[i-1][j];
				if(j>=len[i])
					dp[i][j] |=  dp[i-1][j-len[i]];
			}
		}
		
		int p;
		for(int i=d;i>=0;i--)
			if(dp[n][i])	{p=i;break;}
		
		//cout<<flag<<endl;
		flag=0;
		dfs(n,p);
		cout<<endl;
	 }
     return 0;
}
