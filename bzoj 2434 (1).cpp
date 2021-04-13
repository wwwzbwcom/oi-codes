#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<stack>
#include<map>
using namespace std;
const int maxn=100100;
char str[maxn];
int len;
int n;
int x[maxn],y[maxn];
int idx[maxn];
class Tree
{
	private:
		class Graph
		{
			public:
				int v;
				int nxt;	
		}e[maxn*2];
		int pre[maxn],en;
		int dfs(int u,int f)
		{
		//	cout<<u<<"="<<f<<endl;
			tim++;
			lef[u]=tim;		idx[u]=tim;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
			//	cout<<u<<" "<<v<<" "<<i<<endl;
				if(v!=f)	dfs(v,u);
			}
			rig[u]=tim;
		}
	public:
		int r;
		int lef[maxn],rig[maxn],tim;
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
		//	cout<<u<<" "<<v<<endl; 
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{
			dfs(r,-1);
		//	for(int i=1;i<=4;i++)	cout<<i<<" "<<lef[i]<<" "<<rig[i]<<endl;
		}
}tr;
class SZSZ
{
	private: 
		int sto[maxn*2];
		int lowbit(int val)
		{
			return val&-val;
		}
	public:
		int add(int pos,int val)
		{
			for(int i=pos;i<=maxn;i+=lowbit(i))	sto[i]+=val;
		}
		int sum(int pos)
		{
			int ans=0;
			for(int i=pos;i>0;i-=lowbit(i))	ans+=sto[i];
			return ans;	
		}
		int sum(int l,int r)
		{
			return sum(r)-sum(l-1);
		}
}sz;
class AC
{
	private:
		class Node
		{
			public:
				int nxt[26];
				int fai;
				vector <int> end; 
		}n[maxn];
		int nn;
		int pos[maxn];
	public:
		vector <int> qst[maxn];
		map <int,map<int,int> >	ans; 
		
		int r;
		AC()
		{
			r=++nn;
		}
		void insert()
		{
			int u=r,cnt=0;
			stack <int> sta;	sta.push(u);
			for(int i=0;i<len;i++)
			{
				if('a'<=str[i]&&str[i]<='z')
				{
					if(n[u].nxt[str[i]-'a']==0)	n[u].nxt[str[i]-'a']=++nn;
					u=n[u].nxt[str[i]-'a'];
					sta.push(u);
				}
				else
				{
					if(str[i]=='P')	cnt++,n[u].end.push_back(cnt),pos[cnt]=u;
					if(str[i]=='B') sta.pop(),u=sta.top();
				}
			}
		}
		void build()
		{
			queue <int> que;
			for(int i=0;i<26;i++)
			{
				if(n[r].nxt[i]==0)	n[r].nxt[i]=r;
				else
				{
					n[n[r].nxt[i]].fai=r,que.push(n[r].nxt[i]);
					tr.addedge(n[r].nxt[i],n[n[r].nxt[i]].fai);
				}
			}
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=0;i<26;i++)
				{
					if(n[u].nxt[i]==0)	n[u].nxt[i]=n[n[u].fai].nxt[i];
					else
					{
						n[n[u].nxt[i]].fai=n[n[u].fai].nxt[i],que.push(n[u].nxt[i]);		
						tr.addedge(n[u].nxt[i],n[n[u].nxt[i]].fai);
					}
				}
			}
			tr.r=r;
			tr.build();
		}
		void match()
		{
			int u=r,cnt=0;
			stack <int> sta;	sta.push(u);	sz.add(idx[u],1);
			for(int i=0;i<len;i++)
			{
				if('a'<=str[i]&&str[i]<='z')
				{
					u=n[u].nxt[str[i]-'a'];
					sta.push(u);
					sz.add(idx[u],1);
				}
				else
				{
					if(str[i]=='P')
					{
						for(int j=0;j<n[u].end.size();j++)
						{
							int y=n[u].end[j];
							for(int k=0;k<qst[y].size();k++)
							{
								int x=qst[y][k];
								ans[x][y]=sz.sum(tr.lef[pos[x]],tr.rig[pos[x]]);
							}
						}
					}
					if(str[i]=='B')	sz.add(idx[u],-1),sta.pop(),u=sta.top();
				}
			}
		}
}ac;
int main()
{
	scanf("%s",str);
	len=strlen(str);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		ac.qst[y[i]].push_back(x[i]);
	}
	ac.insert();
	ac.build();
	ac.match();
	for(int i=1;i<=n;i++)	printf("%d\n",ac.ans[x[i]][y[i]]);
}
