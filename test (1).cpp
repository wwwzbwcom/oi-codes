#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 25
#define M 11
using namespace std;
int n,m,K;
int size,root;
int son[N][M];
int fail[N];
int end[N];
char s[N];
struct Matrix
{
    int map[N][N];
}a,ans;
Matrix &mul(Matrix &a,Matrix &b)
{
    static Matrix ret;
    memset(ret.map,0,sizeof(ret.map));
    for(int i=1;i<=size;i++)
    {
        for(int j=1;j<=size;j++)
        {
            for(int k=1;k<=size;k++)
            {
                ret.map[i][j]+=a.map[i][k]*b.map[k][j];
            }
            ret.map[i][j]%=K;
        }
    }
    return ret;
}
Matrix &Quick_Power(Matrix &a,int b)
{
    static Matrix ret;
    memset(ret.map,0,sizeof(ret.map));
    for(int i=1;i<=size;i++)ret.map[i][i]=1;
    while(b)
    {
        if(b&1)ret=mul(ret,a);
        a=mul(a,a);
        b>>=1;
    }
    return ret;
}
void init()
{
    memset(son,-1,sizeof(son));
    root=++size;
}
void ins()
{
    int len=strlen(s+1);
    int now=root;
    for(int i=1;i<=len;i++)
    {
        int alpha=s[i]-'0';
        if(son[now][alpha]==-1)son[now][alpha]=++size;
        now=son[now][alpha];
    }
    end[now]=1;
}
void build()
{
    queue<int>q;
    for(int i=0;i<=9;i++)
    {
        if(son[root][i]==-1)son[root][i]=root;
        else
        {
            fail[son[root][i]]=root;
            q.push(son[root][i]);
        }
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        if(end[fail[u]])end[u]=1;
        for(int i=0;i<=9;i++)
        {
            if(son[u][i]==-1)son[u][i]=son[fail[u]][i];
            else
            {
                fail[son[u][i]]=son[fail[u]][i];
                q.push(son[u][i]);
            }
        }
    }
}
void Build_Matrix()
{
    for(int i=1;i<=size;i++)
    {
        if(end[i])continue;
        for(int j=0;j<=9;j++)
        {
            if(end[son[i][j]])continue;
            a.map[i][son[i][j]]++;
        }
    }
}
int main()
{
    init();
    scanf("%d%d%d",&n,&m,&K);
    scanf("%s",s+1);
    ins();
    build();
    Build_Matrix();
    for(int i=1;i<=size;i++)
    {
    	for(int j=1;j<=size;j++)
    		cout<<a.map[i][j]<<" ";
    	cout<<endl;
	}
    ans=Quick_Power(a,n);
    int print=0;
    for(int i=1;i<=size;i++)
        print=(print+ans.map[1][i])%K;
    printf("%d\n",print);
} 
