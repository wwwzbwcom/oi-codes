#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
#include<string>
#include<set>
using namespace std;
struct mgqS
{
    int g1,p1;
    int g2,p2;
    int num;
    mgqS(){ }
    mgqS(int g1i,int p1i,int g2i,int p2i,int numi){g1=g1i;  p1=p1i; g2=g2i; p2=p2i; num=numi;}
    bool operator<(const mgqS &in)const
    {
        return num>in.num;
    }
};
int n,m;
vector <int> sto[5001000];
priority_queue <mgqS> mgq;
set <int> lis,dif;
int msgflag=0;
void in()
{
    int g,num;scanf("%d%d",&g,&num);
    g--;
    sto[g].push_back(num);
     
    int p=sto[g].size()-1;
     
    if(g+1!=n)  mgq.push( mgqS( g,p,g+1,0,abs(sto[g][p]-sto[g+1][0]) ) );
    if(p!=0)    mgq.push( mgqS( g,p,g,p-1,abs(sto[g][p]-sto[g][p-1]) ) );
     
    if(lis.find(num)!=lis.end())    msgflag=1;
    lis.insert(num);
    set <int> ::iterator it=lis.find(num),jt=lis.find(num);
    if(it!=lis.begin()) jt--,dif.insert( abs(*(it)-*(jt)) );
    jt=it;jt++;
    if(jt!=lis.end())   dif.insert( abs(*(it)-*(jt)) );
}
bool check(mgqS mgq)
{
    if(mgq.g1==mgq.g2)
    {
        if(abs(mgq.p1-mgq.p2)==1)   return 1;
        else    return 0;
    }
    else
    {
        if(mgq.g1+1==mgq.g2)
        {
            if(mgq.p1==sto[mgq.g1].size()-1&&mgq.p2==0) return 1;
            else    return 0;
        }
        else
        {
            if(mgq.g1==mgq.g2+1)
            {
                if(mgq.p2==sto[mgq.g2].size()-1&&mgq.p1==0) return 1;
                else    return 0;
            }
            else    return 0;
        }
    }
}
void mg()
{
    while(1)
    {
        if(mgq.empty()) while(1);
        mgqS cur=mgq.top();
        if(check(cur))
        {
            printf("%d\n",cur.num);
            break;
        }
        else    mgq.pop();
    }
}
void msg()
{
    if(msgflag==1)  printf("0\n");
    else    printf("%d\n",*dif.begin());
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int t;  scanf("%d",&t);
         
        sto[i].push_back(t);
         
        if(i!=0)    mgq.push( mgqS(i,0,i-1,0,abs(sto[i][0]-sto[i-1][0]) ) );
         
        if(lis.find(t)!=lis.end())  msgflag=1;
        lis.insert(t);
        set <int> ::iterator it=lis.find(t),jt=lis.find(t);
        if(it!=lis.begin()) jt--,dif.insert( abs(*(it)-*(jt)) );
        jt=it;jt++;
        if(jt!=lis.end())   dif.insert( abs(*(it)-*(jt)) );
    }
    for(int i=0;i<m;i++)
    {
        char cmd[20];scanf("%s",cmd);
        if(cmd[0]=='I')   in();
        if(cmd[0]=='M'&&cmd[4]=='G')  mg();
        if(cmd[0]=='M'&&cmd[4]=='S') msg();
    }
}
