#include<cstdlib>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<map>
#include<set>
using namespace std;
const int maxn=100100;
int tmp[maxn*2];
class String
{
	public:
		int len;
		int *str;
		String()
		{
			str=0;
		}
		void input(int mod)
		{
			if(mod==0)
			{
				if(str!=0)	free(str);
				scanf("%d",&len);
				str=(int*)malloc((len+5)*(sizeof(int)));
				int flag=0;
				for(int i=0;i<len;i++)	scanf("%d",&str[i]);
			}
			else
			{
				if(str!=0)	free(str);
				scanf("%d",&len);
				for(int i=0;i<len;i++)	scanf("%d",&tmp[i]);
				tmp[len]=-1e9; 
				int t;
				scanf("%d",&t);
				for(int i=0;i<t;i++)	scanf("%d",&tmp[len+i+1]);
				len+=t+1;
				str=(int*)malloc((len+5)*(sizeof(int)));
				memcpy(str,tmp,((sizeof(int))*(len)));
			}
		}
}s[maxn];
int ans1[maxn];
int ans2[maxn];
set <int> boo;
int n,m;
class AC
{
	private:
		class Node
		{
			public:
				map <int,int> nxt;
				int fail;
				vector <int> end;
		}n[maxn];
		int nn,r;
	public:
		AC()
		{
			r=1;
			nn=1;
		}
		void insert(int p,const String &in)
		{
			int u=r;
			for(int i=0;i<in.len;i++)
			{
				if(n[u].nxt.find(in.str[i])==n[u].nxt.end())	n[u].nxt[in.str[i]]=++nn;
				u=n[u].nxt[in.str[i]];
			}
			n[u].end.push_back(p);
		}
		void build()
		{
			queue <int> que;
			n[r].fail=r;
			for(map <int,int>::iterator it=n[r].nxt.begin();it!=n[r].nxt.end();it++)
				n[(*it).second].fail=r,que.push((*it).second);
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(map<int,int>::iterator it=n[u].nxt.begin();it!=n[u].nxt.end();it++)
				{
					int tmp=n[u].fail;	que.push((*it).second); 
					while(tmp!=r&&n[tmp].nxt.find((*it).first)==n[tmp].nxt.end())	tmp=n[tmp].fail;
					if(n[tmp].nxt.find((*it).first)!=n[tmp].nxt.end())	n[(*it).second].fail=n[tmp].nxt[(*it).first];
					else	n[(*it).second].fail=tmp;
				}
			}
		}
		int match(const String &in)
		{
			int u=r;
			int ans=0;
			boo.clear();
			for(int i=0;i<in.len;i++)
			{
				//cout<<i<<"="<<endl;
				while(u!=r&&n[u].nxt.find(in.str[i])==n[u].nxt.end())	u=n[u].fail;
				if(n[u].nxt.find(in.str[i])!=n[u].nxt.end())	u=n[u].nxt[in.str[i]];
				int tmp=u;
				while(tmp!=r)
				{
					for(int i=0;i<n[tmp].end.size();i++)	boo.insert(n[tmp].end[i]);
					tmp=n[tmp].fail;
				}
			}
			for(set<int>::iterator it=boo.begin();it!=boo.end();it++)	ans1[*it]++,ans++;
			return ans;
		}
}ac;
int main()
{
//	freopen("name1.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	s[i].input(1);
//	puts("==============================");
	for(int i=1;i<=m;i++)
	{   
		String tmp;	tmp.input(0);
		ac.insert(i,tmp);
	}
	ac.build();
	
	for(int i=1;i<=n;i++)
	{
		ans2[i]=ac.match(s[i]);
	}
	for(int i=1;i<=m;i++)	printf("%d\n",ans1[i]);
	for(int i=1;i<=n;i++)	printf("%d ",ans2[i]);
}
