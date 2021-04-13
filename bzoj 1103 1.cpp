#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1000100;
int n,m;
vector <int> e[maxn];
int vis[maxn];
int sta[maxn],end[maxn],dep[maxn],fat[maxn];
int cnt=0;
int root=0;
int tim=0;
vector <int> q;
void bd()
{   
    for(int i=1;i<=1e8;i++)  q.push_back(i);
}
struct XDS
{
    XDS(){nn=0;}
    struct Node
    {
        int le,re;
        int ls,rs;
        int add;
        int num;
    }no[maxn*4];
    int nn;
    int build(int l,int r)
    {
        int now=nn++;
        no[now].le=l;   no[now].re=r;
        no[now].add=0;
        if(l==r)
        {
            no[now].ls=no[now].rs=-1;
            no[now].num=dep[l];
        }
        else
        {
            int mid=(l+r)/2;
            no[now].ls=build(l,mid);
            no[now].rs=build(mid+1,r);
        }
        return now;
    }
    int query(int now,int p)
    {
        int l=no[now].le,r=no[now].re;
        if(l==r)    return no[now].num+no[now].add;
        else
        {
            int mid=(l+r)/2;
            if(p<=mid)   return query(no[now].ls,p)+no[now].add;
            else    return query(no[now].rs,p)+no[now].add;
        }
    }
    void change(int now,int lc,int rc,int num)
    {
        if(lc>rc)    bd();
        int l=no[now].le,r=no[now].re;
        if(l==lc&&r==rc)    no[now].add+=num;
        else
        {
            if(l==r)    bd();
        //  if(no[now].ls==-1||no[now].rs==-1)  while(1);
            int mid=(l+r)/2;
            if(rc<=mid)  change(no[now].ls,lc,rc,num);
            else
            {
                if(lc>=mid+1)    change(no[now].rs,lc,rc,num);
                else    change(no[now].ls,lc,mid,num),change(no[now].rs,mid+1,rc,num);
            }
        }
    }
}xds;
void dfs(int u,int f,int d)
{
    fat[u]=f;
     
    cnt++;  sta[u]=cnt; dep[cnt]=d;
    for(int i=0;i<e[u].size();i++)
    {
        int v=e[u][i];
        if(v!=f)    dfs(v,u,d+1);
    }
    cnt++;  end[u]=cnt; dep[cnt]=d;
}
int main()
{
    //cin>>n;
    scanf("%d",&n); 
    for(int i=1;i<=n-1;i++)
    {
        int u,v;scanf("%d%d",&u,&v);//cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,-1,0);
    root=xds.build(1,cnt);
    scanf("%d",&m);
    for(int i=1;i<=m+n-1;i++)
    {
        char cmd[10];scanf("%s",cmd);
        if(cmd[0]=='W')
        {
            int p;scanf("%d",&p);
            printf("%d\n",xds.query(root,sta[p]));
        }
        else
        {
            int l,r;scanf("%d%d",&l,&r);
            if(fat[l]==r)   xds.change(root,sta[l],end[l],-1);
            else    xds.change(root,sta[r],end[r],-1);
        }
    }
    return 0;
}
