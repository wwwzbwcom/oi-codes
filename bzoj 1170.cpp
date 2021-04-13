#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const long long bay=130,bax=133;
const long long rey=515384619,rex=624060156;
long long muy[1000100],mux[1000100];
long long hay[1000][1000],hax[1000][1000];
map <int,int> boo;
int yn,xn,yc,xc;
char mat[1100][1100];
int ans=0;
void input()
{
    scanf("%d%d",&yn,&xn);
    getchar();
    for(int i=1;i<=yn;i++)
    {
        for(int j=1;j<=xn;j++)
            mat[i][j]=getchar();
        getchar();
    }
    scanf("%d%d",&yc,&xc);
}
void init()
{
    muy[0]=1;   for(int i=1;i<1000100;i++)   muy[i]=(muy[i-1]*bay)%moy;
    mux[0]=1;   for(int i=1;i<1000100;i++)   mux[i]=(mux[i-1]*bax)%mox;
}
void work()
{
    for(int j=1;j<=xn;j++)
    {
        long long cur=0,cnt=1;
        for(int i=1;i<=yc;i++)   cur=(cur+mat[i][j]*muy[i])%moy;
        hay[cnt++][j]=cur;
        for(int i=yc+1;i<=yn;i++)
        {
            cur=((cur-mat[i-yc][j]*muy[1])%moy*rey)%moy;
            cur=(cur+mat[i][j]*muy[yc])%moy;
            cur=(cur%moy+moy)%moy;
            hay[cnt++][j]=cur;
        }
    }
    for(int i=1;i<=yn-yc+1;i++)
    {
        long long cur=0,cnt=1;
        for(int j=1;j<=xc;j++)   cur=(cur+hay[i][j]*mux[j])%mox;
        hax[i][cnt++]=cur;
        for(int j=xc+1;j<=xn;j++)
        {
            cur=((cur-hay[i][j-xc]*mux[1])%mox*rex)%mox;
            cur=(cur+hay[i][j]*mux[xc])%mox;
            cur=(cur%mox+mox)%mox;
            hax[i][cnt++]=cur;
        }
         
    }
    for(int i=1;i<=yn-yc+1;i++)
        for(int j=1;j<=xn-xc+1;j++)
        {
            boo[hax[i][j]]++;
            if(boo[hax[i][j]]>boo[ans])  ans=hax[i][j];
        }
}
void output()
{
    printf("%d %d\n",yc,xc);
    int flag=0;
    for(int i=1;i<=yn-yc+1;i++)
        for(int j=1;j<=xn-xc+1;j++)
        {
            if(hax[i][j]==ans)
            {
                if(flag==0)
                {
                    flag=1;
                    for(int p=i;p<=i+yc-1;p++)
                    {
                        for(int q=j;q<=j+xc-1;q++)
                            printf("%c",mat[p][q]);
                        printf("\n");
                    }
                    printf("%d\n",boo[ans]);
                }
                printf("%d %d\n",i,j);
            }
        }
}
int main()
{
    input();
    init();
    work();
    output();
}
