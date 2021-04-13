#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
const int maxn=1e5+10;
int n,q;
char tmp[maxn*30];
char *str[maxn];
int sta[maxn],end[maxn],cnt[maxn];
int ssi[maxn],esi[maxn];
int ans[maxn];
class AC
{
	private:
		class Node
		{
			public:
				int nxt[26];
				int fai;
				vector <pair<int,int> > boo;
		}n[maxn];
		int nn,r;
		int cur[maxn];
	public:
		AC()
		{
			r=++nn; 
		} 
		void addstr(char *str,int len,int p,int b)
		{
			int u=r;
			for(int i=0;i<len;i++)
			{
				if(n[u].nxt[str[i]-'a']==0)	n[u].nxt[str[i]-'a']=++nn;
				u=n[u].nxt[str[i]-'a'];
			}
			n[u].boo.push_back(make_pair(p,b));
		}
		void build()
		{
			queue <int>	 que;
			for(int i=0;i<26;i++)
			{
				if(n[r].nxt[i]==0)	n[r].nxt[i]=r;
				else	n[n[r].nxt[i]].fai=r,que.push(n[r].nxt[i]);
			}
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=0;i<26;i++)
				{
					if(n[u].nxt[i]==0)	n[u].nxt[i]=n[n[u].fai].nxt[i];
					else	n[n[r].nxt[i]].fai=n[n[u].fai].nxt[i],que.push(n[r].nxt[i]);
				}
			}
		}
		void match(char *str)
		{
			int u=r;
			int len=strlen(str);
			for(int i=0;i<len;i++)
			{
				u=n[u].nxt[str[i]-'a'];
				for(int j=0;j<n[u].boo.size();j++)
				{
					int p=n[u].boo[j].first,b=n[u].boo[j].second;
					if(cur[p]!=-1&&cur[p]==b)
					{
						cur[p]++;
						if(sta[p]==0&&b==0&&i-ssi[p]+1>0)	cur[p]=-1;
						if(cur[p]==cnt[p])
						{
							if(end[p]==0&&i==len-1)	cur[p]=-1;
							else	ans[p]++;
						}
					}
				}
			}
		}
}ac;
void insert(char *str,int p)
{
	int len=strlen(str);
	if(str[0]=='*')	sta[p]=1;
	if(str[len-1]=='*')	end[p]=1;
	int las=0,con=0;
	for(int i=0;i<len;i++)
	{
		if(str[i]=='*')
		{
			if(con==1)
			{
				ac.addstr(str+las,i-las,p,cnt[p]);
				if(cnt[p]==0)ssi[p]=i-las;
				esi[p]=i-las;
				cnt[p]++;
			}
		}
		else
		{
			if(con==0)	las=i,con=1;
		}
	}
}
int main()
{
	cin>>n>>q;
	for(int i=0;i<n;i++)
	{
		cin>>tmp;
		int len=sizeof tmp;
		str[i]=(char*)malloc((len+5)*sizeof(char));
		memcpy(str,tmp,(len+5)*sizeof(char));
	}
	for(int i=0;i<q;i++)
	{
		cin>>tmp;
		insert(tmp,i);
	}
	ac.build();
	for(int i=0;i<n;i++)	ac.match(str[i]);
	for(int i=0;i<q;i++)	cout<<ans[i]<<endl;
}
