#include<cstdio>
using namespace std;
const int maxn=100100;
int bit[40][2];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=30;i++)   bit[i][0]=0,bit[i][1]=1;
    for(int i=1;i<=n;i++)
    {
        char cmd[10];   int val;
        scanf("%s%d",cmd,&val);
        for(int j=0;j<=30;j++)
        {
            int tmp=((val>>j)&1);
            if(cmd[0]=='O') bit[j][0]|=tmp,bit[j][1]|=tmp;
            if(cmd[0]=='X') bit[j][0]^=tmp,bit[j][1]^=tmp;
            if(cmd[0]=='A') bit[j][0]&=tmp,bit[j][1]&=tmp;
        }
    }
//  for(int i=0;i<=30;i++)   cout<<i<<"="<<bit[i][0]<<"="<<bit[i][1]<<endl; 
    int cur=0,ans=0;
    for(int i=30;i>=0;i--)
    {
        if(bit[i][0])   ans+=(1<<i);
        else    if(bit[i][1]&&cur+(1<<i)<=m)   cur+=(1<<i),ans+=(1<<i);    
    }
    printf("%d",ans);
}
