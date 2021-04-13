#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
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
			public: 
				int nxt[26];
				int fail;
				int step;
				int sum[2];
		}n[maxn];
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn];
		int pre[maxn],en=0;
		int ind[maxn];
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		}
		int nn,last;
		int vis[maxn],tim[maxn];
		void insert(int c)
		{
			int u=last,v=++nn;	tim[v]=1; //cout<<"=";
			n[v].step=n[u].step+1;
			while(u&&n[u].nxt[c]==0)	n[u].nxt[c]=v,u=n[u].fail;
			if(u==0)	n[v].fail=r;
			else
			{
				int uc=n[u].nxt[c];
			//	cout<<u<<" "<<uc<<" "<<c<<" "<<n[u].step<<" "<<n[uc].step<<endl;
				if(n[u].step+1!=n[uc].step)
				{
				//	cout<<"="<<endl;
					int ucc=++nn;	n[ucc]=n[uc];
					n[ucc].fail=n[uc].fail;	n[uc].fail=n[v].fail=ucc;
					while(u&&n[u].nxt[c]==uc)	n[u].nxt[c]=ucc,u=n[u].fail;
				}
				else	n[v].fail=uc;
			}
			last=v;
		}
		void dfs1(int u)
		{
			vis[u]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(vis[v]==0)	dfs1(v);
			}
		//	cout<<n[u].fail<<" "<<u<<" "<<tim[u]<<endl;
			tim[n[u].fail]+=tim[u];
		}
		void dfs2(int u)
		{
			vis[u]=1;
			n[u].sum[0]=1;
			n[u].sum[1]=tim[u];
			for(int i=0;i<26;i++)
			{
				int v=n[u].nxt[i];
				if(v!=0&&vis[v]==0)	dfs2(v);
				if(v!=0)	n[u].sum[0]+=n[v].sum[0],n[u].sum[1]+=n[v].sum[1];
			}
		}
	public:
		int r;
		SAM()
		{
			memset(pre,-1,sizeof pre);
			tim[r]=1;
			r=++nn;
			last=r;
		}
		void build()
		{
			for(int i=0;i<len;i++)	insert(str[i]-'a');
			for(int i=1;i<=nn;i++)	addedge(n[i].fail,i),ind[i]++;
			memset(vis,0,sizeof vis);	dfs1(0);
			//for(int i=1;i<=nn;i++)	cout<<i<<" "<<n[i].sum[0]<<" "<<tim[i]<<" "<<n[i].sum[1]<<endl;
			memset(vis,0,sizeof vis);	dfs2(r);
			//for(int i=1;i<=nn;i++)	cout<<i<<" "<<n[i].sum[0]<<" "<<tim[i]<<"="<<n[i].sum[1]<<endl;
		}
		bool find(int u,int res)
		{
			if(res<=0)	return 1;
			int tmp=0; 
			for(int i=0;i<26;i++)
			{
				int v=n[u].nxt[i];
				if(v!=0)
				{
					tmp+=n[v].sum[t];
					if(tmp>=res)
					{
						char c='a'+i;	cout<<c;
						if(t==0)	return find(v,res-(tmp-n[v].sum[t])-1);
						else	return find(v,res-(tmp-n[v].sum[t])-tim[v]);
					}
				}
			}
			return 0;
		}
}sa;
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%s",str);
	len=strlen(str);
	sa.build();
	/*
	t=1;	k=50;
	for(int i=1;i<=k;i++)
	{
		if(!sa.find(sa.r,i))	cout<<"-1";
		cout<<endl;
	}
	*/
	//cin>>t>>k;
	scanf("%d%d",&t,&k);
	if(!sa.find(sa.r,k))	printf("-1");
}
