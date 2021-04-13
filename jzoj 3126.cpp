//#include<iostream>
#include<algorithm> 
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
const int maxn=1001000;
int n,m;
char str[maxn];
int ans[maxn];
struct Dict_Tree
{
	struct Node
	{
		int nxt[30];
	}n[maxn];
	int r;
	int nn;
	void insert(char *str)
	{
		int u=r;
		int len=strlen(str);
		for(int i=0;i<len;i++)
		{
			if(n[u].nxt[str[i]]==0)	n[u].nxt[str[i]]=++nn;
			u=n[u].nxt[str[i]];
		}
	}
	int match(char *str)
	{
		int u=r;
		int ans=0;
		int len=strlen(str);
		for(int i=0;i<len;i++)
		{
			if(n[u].nxt[str[i]]==0)	break;
			else
			{
				u=n[u].nxt[str[i]];
				ans++;
			}
		}
		return ans;
	}
}dt;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		ans[i]=max(ans[i-1],dt.match(str));
	//	cout<<i<<" "<<ans[i]<<endl;
		dt.insert(str);
	}
	for(int i=1;i<=m;i++)
	{
		int x;	scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
}
