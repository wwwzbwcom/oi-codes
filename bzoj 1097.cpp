#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int oo=1e9+1e8;
struct Edge
{
    int v,c;
    int nxt;
}e[500000];
struct nod4dij
{
    int u,d;
    nod4dij(int ui,int di){u=ui;d=di;}
    bool operator <(const nod4dij &in)const
    {
        return d>in.d;
    }
};
int pre[30000],en=0;
int n,m,k,q;
int vis[30000];
int sta[30000],end[30000];
int dis[50][50];
int spec;
int fob[1210000];
int dyp[1210000][30];
int ans=oo;
void addedge(int u,int v,int c)
{
    e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
    e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
 
void dijstra(int s)
{
    priority_queue <nod4dij> que;
    que.push(nod4dij(s,0));
    while(!que.empty())
    {
        nod4dij cur=que.top();que.pop();
        int u=cur.u,d=cur.d;
        if(vis[u]==0)
        {
            vis[u]=1;
            if(s==1&&u==n)	spec=d;
            if(2<=u&&u<=k+1)
            {
                if(s==1)	sta[u-2]=d;
				else
                {
                    if(s==n)    end[u-2]=d;
                    else    dis[s-2][u-2]=d;
                }
            }
            for(int i=pre[u];i!=-1;i=e[i].nxt)
            {
                int v=e[i].v,c=e[i].c;
                if(vis[v]==0)   que.push(nod4dij(v,d+c));
            }
        }
    }
}
void genfob(int p,int u,int v,int cur)
{
    if(p==k)
    {
        fob[cur]=1;
        return;
    }
    if(p!=u-2&&p!=v-2)
    {
        genfob(p+1,u,v,cur);
        genfob(p+1,u,v,cur+(1<<p)); 
    }
    else
    {
        if(p==u-2)  genfob(p+1,u,v,cur);
        if(p==v-2)  genfob(p+1,u,v,cur+(1<<p)); 
    }
}
int main()
{
    memset(pre,-1,sizeof pre);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v,c;scanf("%d%d%d",&u,&v,&c);
        addedge(u,v,c);
    }
    
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        genfob(0,u,v,0); 
    }
     
    for(int i=1;i<=k+1;i++)
    {
        memset(vis,0,sizeof vis);
        dijstra(i);
    }
    memset(vis,0,sizeof vis);
    dijstra(n);
    
    for(int i=1;i<(1<<k);i++)  for(int j=0;j<k;j++) dyp[i][j]=oo;
    for(int j=0;j<k;j++)	dyp[0][j]=sta[j];
    for(int i=0;i<(1<<k);i++)    if(fob[i]==0)
    {
	    for(int p=0;p<k;p++)	if((i&(1<<p))==0)
            for(int j=0;j<k;j++)
                dyp[i|(1<<p)][p]=min(dyp[i|(1<<p)][p],dyp[i][j]+dis[j][p]);
    }
    for(int i=0;i<k;i++) ans=min(ans,dyp[(1<<k)-1][i]+end[i]);
   	if(k!=0)	printf("%d",ans);
	else	printf("%d",spec);
}
