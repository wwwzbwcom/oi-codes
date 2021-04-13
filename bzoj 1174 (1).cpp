#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>
#include<map>
using namespace std;
const int mod=1e7+9;
struct List
{
    int las,nxt;
    int cur;
}lis[1000100];
int sta,end;
map <int,int> boo;
string str[1000100];
int has[1000100];
int mul[1000100];
int n,len,ans;
void init()
{
    mul[0]=1;
    for(int i=1;i<1000100;i++)
    {
        mul[i]=mul[i-1]*130;
        mul[i]%=mod;
    }
}
int main()
{
    init();
    scanf("%d",&n);getchar();
    for(int i=0;i<n;i++)
    {
        char t;
        while(t=getchar())
        {
            if(t=='\n') break;
            else    str[i]+=t;
        }
        len=max(len,(int)str[i].size());
    }
    sta=0,end=n+1; 
    for(int i=0;i<=n+1;i++)
    {
        lis[i].las=i-1;
        lis[i].nxt=i+1;
        lis[i].cur=i-1;
    }
    for(int i=0;i<len;i++)
    {
    	boo.clear();
        for(int j=lis[sta].nxt;j!=end;j=lis[j].nxt)
        {
            int p=lis[j].cur;
            if(str[p].size()==i)
            {
                lis[lis[j].las].nxt=lis[j].nxt;
                lis[lis[j].nxt].las=lis[j].las;
            }
            has[p]+=str[p][i]*mul[i];
            has[p]%=mod;
            int t=boo[has[p]]++;
            ans=max(ans,t*(i+1));
        }
    }
    printf("%d\n",ans);
}
