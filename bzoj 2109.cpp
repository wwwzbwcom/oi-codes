#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
#include<list>
using namespace std;
const int maxn=2010;
int n,m;
int k[maxn];
class Graph
{
    private:
        class Edge
        {
            public: int v,nxt;
        }e[maxn*10];
        int pre[maxn],en;
        int deg[maxn];
        int lis[maxn][maxn],lin[maxn];
        stack <int> sta;
    public:
        Graph()
        {
            memset(pre,-1,sizeof pre);  en=0;
        }
        void addedge(int u,int v)
        {
            e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
        }
        int work(int mod)
        {
            memset(deg,0,sizeof deg);
            memset(lin,0,sizeof lin);
            for(int i=0;i<en;i++)    deg[e[i].v]++;
            for(int i=1;i<=n;i++)    if(i!=mod&&deg[i]==0)  lis[k[i]][lin[k[i]]++]=i;
            int ans=1,cnt=0;
            for(int p=1;p<=n;p++)
            {
                ans+=lin[p];
                cnt+=lin[p];
                if(p>cnt)    return ans;
                for(int q=0;q<lin[p];q++)
                {
                    int u=lis[p][q];
                    if(mod==0)  sta.push(u);
                    for(int i=pre[u];i!=-1;i=e[i].nxt)
                    {
                        int v=e[i].v;
                        deg[v]--;
                        if(v!=mod&&deg[v]==0)
                        {
                            if(k[v]<=p+1)   lis[p+1][lin[p+1]++]=v;
                            else            lis[k[v]][lin[k[v]]++]=v;   
                        }   
                    }
                }
            }
            if(mod!=0)  return ans;
            while(!sta.empty()) printf("%d ",sta.top()),sta.pop();
            printf("\n");
            return 0;
        }
}gp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)    scanf("%d",&k[i]),k[i]=n-k[i]+1;
    for(int i=1;i<=m;i++)
    {
        int u,v;    scanf("%d%d",&u,&v);
        gp.addedge(v,u);
    }
//    gp.work(0);
//  return 0;
    for(int i=1;i<=n;i++)    printf("%d ",n-gp.work(i)+1);
}
?
