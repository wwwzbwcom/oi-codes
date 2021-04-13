#include<cstring>
#include<cstdio>
using namespace std;
int n;
struct Edge
{
    int v;
    int nxt;
}e[5000100];
int pre[1000100],en;
void addedge(int u,int v)
{
    e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
    e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
int aim[1000100];
int ind[1000100];
int vis[1000100];
int que[1000100],qn=0;
int bsiz,lcnt;
bool dfs(int u)
{
    vis[u]=1;
    bsiz++;
    bool ans=0;
    if(ind[u]==0)   lcnt++,ans=1;
    for(int i=pre[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].v;
        if(vis[v]==0)
        {
            if(dfs(v)==1)   ans=1;
        }
    }
// 
    return ans;
}
int most()
{
    memset(ind,0,sizeof ind);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++)    ind[aim[i]]++;
    int ans=0;
      
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            bsiz=0,lcnt=0;
            int con=dfs(i);
            if(bsiz==1) ans++;
            else
            {
                if(con==1)  ans+=bsiz-lcnt;
                else    ans+=bsiz-1;
            }
        }
    }
//  if(n==1e6)  return 0;
    return ans;
}
int least()
{
    memset(ind,0,sizeof ind);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++)    ind[aim[i]]++;
    int ans=0;
      
    for(int i=1;i<=n;i++)    if(ind[i]==0)   vis[i]=1,que[qn++]=i;
    while(qn)
    {
        int u=que[qn-1];qn--;
        int v=aim[u];
        if(vis[v]==0)
        {
            vis[v]=1;
            ans++;
            ind[aim[v]]--;
              
            if(vis[aim[v]]==0&&ind[aim[v]]==0)
            {
                vis[aim[v]]=1;
                que[qn++]=aim[v];
            }
        }
    }
  
    for(int i=1;i<=n;i++)
        if(vis[i]==0)
        {
            bsiz=0,lcnt=0;
            if(dfs(i)==0)
            {
                if(bsiz%2==1)   ans+=bsiz/2+1;
                else    ans+=bsiz/2;
            }
        }
// 
    return ans;
}
int main()
{
//	freopen("maf13b.in","r",stdin);
    memset(pre,-1,sizeof pre);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&aim[i]);
        addedge(i,aim[i]);
    }
    printf("%d %d",least(),most());
}
