#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue> 
using namespace std;
const int maxn=1010;
const int maxm=10010;
int n,m;
int num[maxn];
int l[maxm],r[maxm],p[maxm];
int fir[maxn],cnt[maxn],buf[maxn];
struct FYL
{
	struct EDGE
	{
		int v,c,f;
		int nxt; 
	}e[maxm*2+maxn*4];
	int pre[maxn],en;
	int vis[maxn];
	
	int sta,end;
	int inq[maxn];
	long long dis[maxn];
	long long fee,flo;
	FYL()
	{
		memset(pre,-1,sizeof pre);	en=0;
		fee=0;	flo=0;
	}
	void addedge(int u,int v,int c,int f)
	{
	//	cout<<u<<" "<<v<<" "<<c<<" "<<f<<endl;
		e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
	}
	bool spfa()
	{
		for(int i=1;i<=end;i++)	dis[i]=1e15;	queue <int> que;	memset(inq,0,sizeof inq);
		dis[sta]=0;	que.push(sta);	que.push(sta);	inq[sta]=1;
		while(!que.empty())
		{
			int u=que.front();	que.pop();	inq[u]=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(c&&dis[u]+f<dis[v])
				{
					dis[v]=dis[u]+f;
					if(inq[v]==0)
					{
						inq[v]=1;
						que.push(v);
					}
				}
			}
		}
		if(dis[end]==1e15)	return 0;
		else	return 1;
	}
	long long dfs(int u,long long lc)
	{
		if(u==end)
		{
		//	cout<<lc<<" "<<dis[end]<<endl;
			fee+=lc*dis[end];
			return lc;
		}
		long long nc=0;	vis[u]=1;
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c,f=e[i].f;
			if(vis[v]==0&&c&&dis[u]+f==dis[v])
			{
				int cc=min((long long)c,lc-nc);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		return nc;
	}
	void work()
	{
		while(spfa())
		{
			int t;
			do
			{
				memset(vis,0,sizeof vis);
				t=dfs(sta,1e15);
				flo+=t;
			}while(t);
		}
	}
}fy;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&num[i]);
	for(int i=1;i<=m;i++)	scanf("%d%d%d",&l[i],&r[i],&p[i]);
	
	fy.sta=n+2;	fy.end=n+3;
	for(int i=1;i<=n+1;i++)
	{
		if(num[i]-num[i-1]>=0)	fy.addedge(fy.sta,i,num[i]-num[i-1],0);
		else					fy.addedge(i,fy.end,-num[i]+num[i-1],0);
		
		if(i>1)	fy.addedge(i,i-1,1e9,0);
	}
	for(int i=1;i<=m;i++)	fy.addedge(l[i],r[i]+1,1e9,p[i]);
	/*
	for(int i=1;i<=n+1;i++)
	{
		memset(cnt,0,sizeof cnt);
		for(int j=1;j<=m;j++)	if(l[j]<=i&&i<=r[j])	cnt[j]++;
	//	cout<<i<<"================"<<endl;
	//	for(int j=1;j<=m;j++)	cout<<cnt[j]<<" "<<buf[j]<<" "<<cnt[j]-buf[j]<<endl;
		for(int j=1;j<=m;j++)	if(cnt[j]-buf[j]==1)	fir[j]=i;
		for(int j=1;j<=m;j++)	if(cnt[j]-buf[j]==-1)	fy.addedge(fir[j],i,1e9,p[j]);
		memcpy(buf,cnt,sizeof cnt); 
	}
	*/
	fy.work();
	printf("%d",fy.fee);
}
