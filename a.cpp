#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;
const int inf=100000000,N=110;
struct ee{int to,next,f;}e[N*N*N];
int head[N*N],q[N*N],dis[N*N],a[N][N],b[N][N],c[N][N],col[N][N];
int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
int S,T=10001,n,m,cnt=1,ans,w,mid,tot;
bool mark[N]; 
void ins(int u,int v,int w)
{cout<<u<<" "<<v<<" "<<w<<endl,cnt++;e[cnt].to=v;e[cnt].f=w;e[cnt].next=head[u];head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
   
bool bfs(){
    for (int i=1;i<=T;i++) dis[i]=inf;
    int h=0,t=1,now;
    q[1]=S;dis[S]=0;
    while(h!=t){
        now=q[++h];
        for (int i=head[now];i;i=e[i].next){
            int v=e[i].to;
            if (e[i].f&&dis[now]+1<dis[v]){
                dis[v]=dis[now]+1;
                if (v==T)return 1;
                q[++t]=v;
            }
        }
    }
    if (dis[T]==inf) return 0; return 1;
}
   
int dinic(int now,int f){
    if (now==T) return f;
    int rest=f;
    for (int i=head[now];i;i=e[i].next){
        int v=e[i].to;
        if (e[i].f&&dis[v]==dis[now]+1&&rest){
            int t=dinic(v,min(rest,e[i].f));
            if (!t) dis[v]=0;
            e[i].f-=t;
            e[i^1].f+=t;
            rest-=t;
        }
    }
    return f-rest;
}
 
void build(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
            if(col[i][j]) swap(a[i][j],b[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            insert(S,(i-1)*m+j,a[i][j]);
            insert((i-1)*m+j,T,b[i][j]);
            ans+=a[i][j];ans+=b[i][j];
            if(col[i][j])
            for(int k=0;k<4;k++){
                int nx=i+fx[k],ny=j+fy[k];
                if(nx>n||nx<1||ny>m||ny<1) continue;
                ins((nx-1)*m+ny,(i-1)*m+j,c[i][j]+c[nx][ny]);
                ins((i-1)*m+j,(nx-1)*m+ny,c[i][j]+c[nx][ny]);
                ans+=(c[i][j]+c[nx][ny]);
            }
        }
}
 
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&b[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&c[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
        if ((i+j)&1==1) col[i][j]=1;
    build();
    cout<<S<<"="<<T<<"="<<ans<<endl;
    while(bfs()) tot+=dinic(S,inf);
    printf("%d",ans-tot);
}
