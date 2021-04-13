#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1e6;
char str[maxn];
int len;
int t,k;
class SAM
{
	private:
		class Node
		{
			int nxt[26];
			int fail;
			int step;
			int sum[2];
		}n[maxn];
		int nn,last;
		int vis[maxn],tmp[maxn],tim[maxn];
		void insert(int c)
		{
			int u=last,v=++nn;
			n[v].step=n[u].step+1;
			while(!u&&n[u].nxt[c]==0)	nxt[c]=v,u=n[u].fail;
			if(u==0)	n[v].fail=r;
			else
			{
				int uc=n[u].nxt[c];
				if(n[u].step!=n[uc].step+1)
				{
					int ucc=++nn;	n[ucc]=n[uc];
					n[ucc].fail=n[uc].fail;	n[uc].fail=n[v].fail=ucc;
					while(!u&&n[u].nxt[c]==uc)	n[u].nxt[c]=ucc,u=n[u].fail;
				}
				else	n[u].fail=uc;
			}
		}
		void bfs()
		{
			queue <int> que;	que.push(r);
			vis[r]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=0;i<26;i++)
				{
					int v=n[u].nxt[i];
					if(v!=0)
					{
						tmp[v]+=tmp[u];
						if(vis[v]==0)
						{
							vis[v]=1;
							que.push(v);
						}
					}
				}
			}
		}
		void dfs(int u)
		{
			vis[u]=1;
			tim[u]=1;
			n[u].sum[0]=tmp[u];
			for(int i=0;i<26;i++)
			{
				int v=n[u].nxt[i];
				if(v!=0)
				{
					if(vis[v]==0)	dfs(v);
					n[u].sum[0]+=n[v].sum[0];
					tim[u]+=tim[v];
					n[u].sum[1]+=n[v].sum[0]*tim[v]; 
				}
			}
		}
	public:
		int r;
		SAM()
		{
			r=++nn;
			last=r;
		}
		void build()
		{
			for(int i=0;i<len;i++)	insert(str[i]-'a');
			memset(vis,0,sizeof vis);	bfs();
			memset(vis,0,sizeof vis);	dfs();
		}
		void find(int u,int res)
		{
			if(res==0)	return;	
			for(int i=0;i<26;i++)
			{
				int v=n[u].nxt[i];
				if(v!=0)
				{
					if(res-n[v].sum[t]>0)	res-=n[v].sum[t];
					else
					{
						char c='a'+i;	cout<<c;
						find(v,res-n[v].sum[t]);
					}
				}
			} 
		}
}
int main()
{
	cin>>str;
	len=strlen(str);
	cin>>t>>k;
	sa.build();
	sa.find(sa.r,res)
}
