//#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
const int maxn=200100;
using namespace std;
int jum[maxn];
struct AC_automachine
{
	struct Node
	{
		int nxt[150];
		int fail;
		int end;
	}n[maxn];
	int nn;
	AC_automachine()
	{
		nn=1;
	}
	void insert(char *str)
	{
		int u=1,len=strlen(str);
		for(int i=0;i<len;i++)
		{
			if(n[u].nxt[str[i]]==0)	n[u].nxt[str[i]]=++nn;
			u=n[u].nxt[str[i]];
		}
		n[u].end=len;
	}
	void build()
	{
		queue <int> que;
		for(int i=0;i<150;i++)
		{
			if(n[1].nxt[i]==0)	n[1].nxt[i]=1;
			else	n[n[1].nxt[i]].fail=1,que.push(n[1].nxt[i]);
		}
		while(!que.empty())
		{
			int u=que.front();que.pop();
			for(int i=0;i<150;i++)
			{
				if(n[u].nxt[i]==0)	n[u].nxt[i]=n[n[u].fail].nxt[i];
				else	n[n[u].nxt[i]].fail=n[n[u].fail].nxt[i],que.push(n[u].nxt[i]);
			}
		}
	}
	void match(char *str)
	{
		stack <int> ust,ist;
		int u=1,i,len=strlen(str+1);
		ist.push(i);	ust.push(u);
		while(i<=len)
		{
			if(n[u].end)
			{
				for(int j=0;j<n[u].end;j++)	jum[ist.top()]=i+1,ust.pop(),ist.pop();
				u=ust.top();	i=ist.top();
			}
			else
			{
				i++;	while(jum[i])	i=jum[i];
				u=n[u].nxt[str[i]];
				ust.push(u);	ist.push(i);
			}
		}
	}
}ac;
char mat[maxn];
char str[maxn];

int n;
int main()
{
	scanf("%s",mat+1);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%s",str);
		ac.insert(str);
	}
	
	ac.build();
	ac.match(mat);
	int len=strlen(mat+1);
	for(int i=1;i<=len;i++)
	{
	//	cout<<i<<" "<<jum[i]<<endl;
		while(jum[i])	i=jum[i];
		putchar(mat[i]);
	}
}
