#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=500100;
struct Edge
{
    int v,c;
    int nxt;
}e[maxn];
int pre[maxn],en=0;
int n,m;
int vis[maxn],dis[maxn],cnt[maxn];
queue <int> que;
int mni=1e9;
long long ans;
void addedge(int u,int v,int c)
{
    e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++; 
}
bool SPFA()
{
    que.push(n+1);
    vis[n+1]=1;
    cnt[n+1]++;
    while(!que.empty())
    {
        int u=que.front();que.pop();vis[u]=0;
        for(int i=pre[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v,c=e[i].c; 
            if(dis[v]>dis[u]+c)
            {
                dis[v]=dis[u]+c;
                cnt[v]++;
                if(cnt[v]>n)   return 0;
                if(vis[v]==0)
                {
                    vis[v]=1;
                    que.push(v);
                }
            }   
        }
    }
    return 1;
}
int main()
{
    memset(pre,-1,sizeof pre);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int cmd,u,v;    scanf("%d%d%d",&cmd,&u,&v);//   cin>>cmd>>u>>v;
        if(cmd==1)  addedge(u,v,0),addedge(v,u,0);
        if(cmd==2)  addedge(v,u,-1);
        if(cmd==3)  addedge(u,v,0);
        if(cmd==4)  addedge(u,v,-1);
        if(cmd==5)  addedge(v,u,0);
    }
    for(int i=n;i>=1;i--)    addedge(n+1,i,0);
    if(SPFA()==0)   printf("-1\n");
    else
    {
    	for(int i=1;i<=n;i++)	mni=min(mni,dis[i]);
    	for(int i=1;i<=n;i++)	dis[i]=dis[i]-mni+1;
        for(int i=1;i<=n;i++)   ans+=dis[i];
        printf("%lld\n",ans);
    }
//  for(int i=1;i<=n;i++)    printf("%d %d\n",i,dis[i]);
}
