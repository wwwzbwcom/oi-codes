#include <stdio.h>  
#include <string.h> 
#include <iostream>
#define N 500010  
using namespace std;
int next[N];  
int nextval[N];  
int extend[N];  
  
char S[N];  
char T[N];  
  
void GetNext(char *T)  
{  
    int a=0;  
    int Tlen=strlen(T);  
    next[0]=Tlen;  
    while(a<Tlen-1&&T[a]==T[a+1]) a++;  
    next[1]=a;  
    a=1;  
    for(int k=2;k<Tlen;k++)  
    {  
        int p=a+next[a]-1,L=next[k-a];  
        if((k-1)+L>=p)  
        {  
            int j=(p-k+1)>0? p-k+1:0;  
            while(k+j<Tlen&&T[k+j]==T[j]) j++;  
            next[k]=j;  
            a=k;  
        }  
        else next[k]=L;  
    }  
}  
  
void GetExtend(char *S,char *T)  
{  
    int a=0;  
    GetNext(T);  
    int Slen=strlen(S);  
    int Tlen=strlen(T);  
    int MinLen=Slen<Tlen? Slen:Tlen;  
    while(a<MinLen&&S[a]==T[a]) a++;  
    extend[0]=a;  
    a=0;  
    for(int k=1;k<Slen;k++)  
    {  
        int p=a+extend[a]-1,L=next[k-a];  
        if((k-1)+L>=p)  
        {  
            int j=(p-k+1)>0? p-k+1:0;  
            while(k+j<Slen&&j<Tlen&&S[k+j]==T[j]) j++;  
            extend[k]=j;  
            a=k;  
        }  
        else extend[k]=L;  
    }  
}  
  
void NextVal(char *T)  
{  
    int i=0,j=-1;  
    nextval[0]=-1;  
    int Tlen=strlen(T);  
    while(i<Tlen)  
    {  
        if(j==-1||T[i]==T[j])  
        {  
            i++;  
            j++;  
            if(T[i]!=T[j]) nextval[i]=j;  
            else  nextval[i]=nextval[j];  
        }  
        else j=nextval[j];  
    }  
}  
  
int main()  
{  
    int Slen,Tlen,i;  
    int t,tt=1;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%s",S);  
        strcpy(T,S);  
        strcat(S,T);  
        GetExtend(S,T);  
        Tlen=strlen(T);  
        Slen=strlen(S);  
        NextVal(T); 
        cout<<T<<endl;
    	cout<<Tlen<<" "<<nextval[Tlen]<<endl;
        int MOD=Tlen-nextval[Tlen];  
        cout<<MOD<<endl;
        int temp=1;  
        if(Tlen%MOD==0) temp=Tlen/MOD;  
        int ans1=0,ans2=0,ans3=0;  
        for(i=0;i<Tlen;i++)  
        {  
            if(extend[i]>=Tlen) ans2++;  
            else if(S[i+extend[i]]<T[extend[i]]) ans1++;  
            else ans3++;  
        }  
        printf("Case %d: %d %d %d\n",tt++,ans1/temp,ans2/temp,ans3/temp);  
    }  
    return 0;  
}  

