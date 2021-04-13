#include<stdio.h>
#include<algorithm>
using namespace std;
 
char opt[5][6] = {"11111","01111","00*11","00001","00000"};
int dx[10]={1,1,-1,-1,2,2,-2,-2};
int dy[10]={2,-2,2,-2,1,-1,1,-1};
 
bool ok(char s[][6])
{
    for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
       if(s[i][j]!=opt[i][j])
          return false;
    return true;
}
 
void out(char s[][6])
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        printf("%c",s[i][j]);
        printf("\n");
    }
}
 
char g[5][6];
int bound;
 
int calc(char s[][6])
{
    int ans = 0;
    for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
     ans += s[i][j] != opt[i][j];
    return ans-1;
}
 
bool judge(char s[][6],int step,int x,int y)
{ 
     
    if(ok(s)) 
        return true;
     
    if(step+calc(s)>bound) return false;
     
    for(int k=0;k<8;k++)
    {
            int nx = x + dx[k], ny = y + dy[k]; 
            if(0<=nx && nx <5 && 0<=ny && ny <5)
            {
                swap(s[x][y],s[nx][ny]);
                if(judge(s,step+1,nx,ny))   return true;
                swap(s[x][y],s[nx][ny]);
            }
    }
    return false;
}
 
int solve()
{
     
    for(int k=0;k<=15;k++)
    {
        bound = k;
        char s[5][6];
        for(int i=0;i<5;i++)
           for(int j=0;j<5;j++)
              s[i][j] = g[i][j];
        int x,y;
    for(int i=0;i<5;i++)
       for(int j=0;j<5;j++)
          if(s[i][j]=='*') x = i, y = j;
     
         
        if(judge(s,0,x,y)) return k;
    }
    return -1;
}
int main()
{
    int gn;
    scanf("%d",&gn);
    while(gn--)
    {
        for(int i=0;i<5;i++)
            scanf("%s",g[i]);
        printf("%d\n",solve());
    }
    return 0;   
}
