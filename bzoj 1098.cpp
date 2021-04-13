#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
vector<int>edg[100100];
void addedge(int u,int v)
{
	edg[u].push_back(v);
	edg[v].push_back(u); 
}
struct LINK
{
	int cur;
	int pre,nxt;
}lin[100100],s,e;
int n,m;
int boo[100100];
int blo[100100],bn=0;
int mar[100100];
int ans[100100],ansn;
void bfs(int sta)
{
	queue <int> que;
	que.push(sta);
	while(!que.empty())
	{
		int u=que.front();que.pop();blo[u]=bn;
		for(int i=0;i<edg[u].size();i++)	boo[edg[u][i]]=u;
	//	cout<<u<<"========================="<<endl;
		for(int i=lin[0].nxt;lin[i].cur!=-1;i=lin[i].nxt)
		{
			int v=lin[i].cur;
			if(boo[v]!=u)
			{
			//	cout<<v<<" ";
				que.push(v);
				lin[lin[i].pre].nxt=lin[i].nxt;
				lin[lin[i].nxt].pre=lin[i].pre;
			}
		}
	//	cout<<endl;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	lin[0].cur=-1;lin[n+1].cur=-1;
	lin[0].nxt=1;lin[n+1].pre=n;
	for(int i=1;i<=n;i++)	lin[i].cur=i,lin[i].pre=i-1,lin[i].nxt=i+1;
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	
	for(int i=1;i<=n;i++)	if(blo[i]==0)	bn++,bfs(i);
	for(int i=1;i<=n;i++)	mar[blo[i]]++;//cout<<i<<" "<<blo[i]<<endl;;
	for(int i=1;i<=n;i++)	if(mar[i]!=0)	ans[++ansn]=mar[i];
	sort(ans+1,ans+ansn+1);
	printf("%d\n",ansn);
	for(int i=1;i<=ansn;i++)	printf("%d ",ans[i]);
	
}
