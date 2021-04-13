#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=(int)1e8;
struct Edge
{
    int v,c;
    int nxt;
}e[300000];
int pre[500],en=0;
int n,m;
int nn;
char map[100][100];
int dor[500],dn;
int dis[500][500];
int sta,end,pn;
int lev[500];
void addedge(int u,int v,int c)
{
    e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
    e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
}
int idx(int i,int j)
{
    return i*m+j;
}
bool inrange(int i,int j)
{
    if(0<=i&&i<n&&0<=j&&j<m)    return 1;
    else    return 0;
}
void init()
{
    for(int i=0;i<500;i++)   for(int j=0;j<500;j++)   dis[i][j]=oo;
    for(int i=0;i<500;i++)   dis[i][i]=0;
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>map[i][j];
            if(map[i][j]!='X')
            {
                for(int p=-1;p<=1;p++)
                    for(int q=-1;q<=1;q++)
                        if(abs(p)+abs(q)==1&&inrange(i+p,j+q)&&map[i+p][j+q]!='X')
                            dis[idx(i,j)][idx(i+p,j+q)]=1;
            }
            if(map[i][j]=='D')  dor[dn++]=idx(i,j);
        }
    nn=n*m;
    for(int k=0;k<nn;k++)    if(map[k/m][k%m]=='.')
        for(int i=0;i<nn;i++)
            for(int j=0;j<nn;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    sta=n*m,end=n*m+1;
}
bool bfs()
{
    memset(lev,-1,sizeof lev);
    queue <int> que;
    que.push(sta);
    lev[sta]=0;
    while(!que.empty())
    {
        int u=que.front();que.pop();
        for(int i=pre[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v,c=e[i].c;
            if(lev[v]==-1&&c>0)
            {
                lev[v]=lev[u]+1;
                que.push(v);
            }
        }
    }
    if(lev[end]==-1)    return 0;
    else    return 1;
}
int dfs(int u,int lc)
{
    int nc=0;
    if(u==end)  return lc;
    for(int i=pre[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].v,c=e[i].c;
        if(lev[v]==lev[u]+1&&c>0)
        {
            int cc=min(c,lc-nc);
            cc=dfs(v,cc);
            nc+=cc;
            e[i].c-=cc;
            e[i^1].c+=cc;
        }
        if(nc==lc)	break; 
    }
    if(nc==0)   lev[u]=-2;
    return nc;
}
int dinic()
{
    int ans=0;
    while(bfs())
    {
        int t=dfs(sta,oo);
        if(t)   ans+=t;
        else    break;
    }
    return ans;
}
bool work(int ti)
{
    en=0;memset(pre,-1,sizeof pre);
    pn=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[i][j]=='.')
            {
                pn++;
                addedge(sta,idx(i,j),1);
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[i][j]=='.')
                for(int k=0;k<dn;k++)
                    if(dis[idx(i,j)][dor[k]]<=ti)    addedge(idx(i,j),dor[k],1);
    for(int i=0;i<dn;i++)    addedge(dor[i],end,ti);
    if(dinic()==pn) return 1;
    else    return 0;
}
int main()
{
    init();
    int l=0,r=500;
    int ans=500;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(work(mid))   r=mid-1,ans=mid;
        else    l=mid+1;    
    }
    if(ans==500)    cout<<"impossible"<<endl;
    else    cout<<ans<<endl;
}
