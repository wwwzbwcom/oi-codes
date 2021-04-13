#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int mod=10007;
const int maxn=110;
int qsm(int a,int b)
{
	if(b==0)	return 1;
	int ans=(qsm(a,b/2)*qsm(a,b/2))%mod;
	if(b%2==0)	return ans%mod;
	else	return (ans*a)%mod;
}
struct acam
{
	int nxt[maxn*60][26];
	int fai[maxn*60];
	int end[maxn*60];
	int nn,root;
	acam(){root=++nn;}
	void insert(char *str)
	{
		int len=strlen(str);
		int now=root;
		for(int i=0;i<len;i++)
		{
			if(nxt[now][str[i]-'A']!=0)	now=nxt[now][str[i]-'A'];
			else	nxt[now][str[i]-'A']=++nn,now=nxt[now][str[i]-'A']; 
		}
		end[now]=1;
	}
	void build()
	{
		queue <int> que;
		for(int i=0;i<26;i++)
		{
			if(nxt[root][i]!=0)	fai[nxt[root][i]]=root,que.push(nxt[root][i]);
			else	nxt[root][i]=root;
		}
		while(!que.empty())
		{
			int now=que.front();que.pop();
			for(int i=0;i<26;i++)
			{
				if(nxt[now][i]!=0)	fai[nxt[now][i]]=nxt[fai[now]][i],que.push(nxt[now][i]);
				else	nxt[now][i]=nxt[fai[now]][i];
				
				if(end[nxt[fai[now]][i]])	end[nxt[now][i]]=1;
			}
		}
	}
}ac;
int dyp[maxn][maxn*60];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		char str[100];	scanf("%s",str);
		ac.insert(str);
	}
	ac.build();
	dyp[0][ac.root]=1;
	for(int i=0;i<m;i++)
	{
		for(int j=1;j<=ac.nn;j++)	if(ac.end[j]==0)
			for(int k=0;k<26;k++)	if(ac.end[ac.nxt[j][k]]==0)
				dyp[i+1][ac.nxt[j][k]]+=dyp[i][j],
				dyp[i+1][ac.nxt[j][k]]%=mod;
	}
	int ans=0;
	for(int i=1;i<=ac.nn;i++)	if(ac.end[i]==0)	ans+=dyp[m][i],ans%=mod;
	printf("%d",(qsm(26,m)-ans+mod)%mod);
}
