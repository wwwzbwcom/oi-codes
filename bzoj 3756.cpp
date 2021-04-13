#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=2000000;
const long long mod=1e9+7; 
int n;
char str[maxn];
int fai[maxn];
int cnt[maxn];
int main()
{
	scanf("%d",&n);
	for(int g=1;g<=n;g++)
	{
		scanf("%s",str+1);
		int len=strlen(str+1);
		long long ans=1;
		int fix=0;
		fai[1]=0;
		cnt[1]=1;
		for(int i=2;i<=len;i++)
		{
			while(fix!=0&&str[fix+1]!=str[i])	fix=fai[fix];
			if(str[fix+1]==str[i])	fix++;
			fai[i]=fix;
			while(fix*2>i)	fix=fai[fix];
			cnt[i]=cnt[fix]+1;
		}
		for(int i=1;i<=len;i++)	cout<<i<<" "<<fai[i]<<endl;
		fix=0;
		for(int i=2;i<=len;i++)
		{
			while(fix!=0&&str[fix+1]!=str[i])	fix=fai[fix];
			if(str[fix+1]==str[i])	fix++;
			
			ans=(ans*(cnt[fix]+1))%mod;
		}
	//	for(int i=1;i<=len;i++)	cout<<i<<"="<<fai[i]<<"="<<cnt[i]<<endl;
		printf("%lld\n",ans);
	}
} 
 
