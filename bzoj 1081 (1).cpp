#include<cstdio>
using namespace std;
int b,n;
char idx[]={"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; 
int sto[10000];
int cnt[10000];
void dfs(int p)
{
    if(p==0)
    {
        for(int i=1;i<=n;i++)    printf("%c",idx[sto[i]]);
        printf("\n");
        return;
    }
    if(cnt[p+1]%2==1)   for(int i=0;i<b;i++) sto[p]=i,cnt[p]++,dfs(p-1);
    if(cnt[p+1]%2==0)   for(int i=b-1;i>=0;i--)  sto[p]=i,cnt[p]++,dfs(p-1);
}
int main()
{
    scanf("%d%d",&n,&b);
    cnt[n+1]=1;
    dfs(n);
}
