#include<iostream>
using namespace std;
int n,m,k;
int ay,ax;
char map[1100][1100];
int dyp[1100][1100][4];
int vis[1100][1100][4];
void dfs(int y,int x,int d)
{
    if(vis[y][x][d])    return;
    vis[y][x][d]=1;
     
    if(y==ay&&x==ax)
    {
        dyp[y][x][d]=1;
        return;
    }
     
    if(map[y][x]=='*'||(!(1<=y&&y<=n&&1<=x&&x<=m)))
    {
        dyp[y][x][d]=0;
        return;
    }
     
    if(d==0)
    {
        if(x>ax) dyp[y][x][0]=0;
        else
        {
            dfs(y-1,x,0);
            dfs(y,x+1,1);
            dyp[y][x][0]=dyp[y-1][x][0]+dyp[y][x+1][1];
            dyp[y][x][0]%=k;
        }
        return;
    }
    if(d==1)
    {
        if(y>ay) dyp[y][x][1]=0;
        else
        {
            dfs(y,x+1,1);
            dfs(y+1,x,2);
            dyp[y][x][1]=dyp[y][x+1][1]+dyp[y+1][x][2];
            dyp[y][x][1]%=k;
        }
    }
    if(d==2)
    {
        if(x<ax) dyp[y][x][2]=0;
        else
        {
            dfs(y+1,x,2);
            dfs(y,x-1,3);
            dyp[y][x][2]=dyp[y+1][x][2]+dyp[y][x-1][3];
            dyp[y][x][2]%=k;
        }
    }
    if(d==3)
    {
        if(y<ay) dyp[y][x][3]=0;
        else
        {
            dfs(y,x-1,3);
            dfs(y-1,x,0);
            dyp[y][x][3]=dyp[y][x-1][3]+dyp[y-1][x][0];
            dyp[y][x][3]%=k;
        }
    }
}
int main()
{
    cin>>n>>m>>k;
    cin>>ax>>ay;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>map[i][j];
    dfs(n,1,0);
    cout<<dyp[n][1][0]<<endl;
}
