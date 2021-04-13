#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct bignum
{
    bignum(){l=0;memset(s,0,sizeof s);}
    int s[2000];
    int l;
    void c2b(char tmp[])
    {
        l=strlen(tmp);
        for(int i=0;i<l;i++) s[l-i-1]=tmp[i]-'0';
    }
    bignum operator/(const int &in)const
    {
        bignum ans;
        ans.l=l;
        int carry=0;
        for(int i=l-1;i>=0;i--)
        {
            ans.s[i]=(carry*10+s[i])/in;
            carry=(carry*10+s[i])%in;
        }
        while(ans.s[ans.l-1]==0&&ans.l>0)    ans.l--;
        return ans;
    }
    int operator%(const int &in)const
    {
        int ans=0;
        for(int i=l-1;i>=0;i--)  ans=(ans*10+s[i])%in;
        return ans;
    }
    void output()
    {
        for(int i=l-1;i>=0;i--)  cout<<s[i];
    }
};
int sto[2000],cnt=0;
void t2f(bignum cur)
{
    while(cur.l>0)
    {
        sto[cnt++]=cur%4;
        cur=cur/4;
    }
}
int dyp[2000][2];
int way[2000][2];
const int mod=1e9;
void update(int ai,int aj,int bi,int bj,int add)
{
    if(dyp[ai][aj]>dyp[bi][bj]+add)
    {
        dyp[ai][aj]=dyp[bi][bj]+add;
        way[ai][aj]=way[bi][bj];
    }
    else    if(dyp[ai][aj]==dyp[bi][bj]+add)  way[ai][aj]+=way[bi][bj],way[ai][aj]%=mod;
}
void work()
{
    for(int i=0;i<2000;i++)  dyp[i][0]=dyp[i][1]=1e9;
    dyp[0][0]=0;
    way[0][0]=1;
    for(int i=0;i<cnt;i++)
    {
        update(i+1,0,i,0,sto[i]);
        update(i+1,0,i,1,sto[i]+1);
        update(i+1,1,i,0,4-sto[i]);
        update(i+1,1,i,1,4-(sto[i]+1));
        
    }
//    for(int i=0;i<=cnt;i++)    cout<<i<<"  "<<dyp[i][0]<<"="<<dyp[i][1]<<"        "<<way[i][0]<<"="<<way[i][1]<<endl;
	int mni=1e9,ans=0;
	if(dyp[cnt][0]<mni)	mni=dyp[cnt][0],ans=way[cnt][0];
	else	if(dyp[cnt][0]==mni)	ans+=way[cnt][0];
	if(dyp[cnt][1]+1<mni)	mni=dyp[cnt][1],ans=way[cnt][1];
	else	if(dyp[cnt][1]+1==mni)	ans+=way[cnt][1];
	ans%=mod;
	cout<<ans;
	
}
int main()
{
    char tmp[2000]; cin>>tmp;
    bignum num; num.c2b(tmp);   t2f(num);
    //for(int i=cnt-1;i>=0;i--)  cout<<sto[i];
    //cout<<endl;
    work();
}
