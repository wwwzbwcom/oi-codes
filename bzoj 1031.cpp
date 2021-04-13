#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200100;
char str[maxn];
int suf[maxn];
int tra[maxn],tsu[maxn];
int buc[maxn],tst[maxn];
void suffix_array(char *str,int *su1,int n,int m)
{
	int *ra1=tra,*su2=tsu,*tmp;
	for(int i=0;i<m;i++)	buc[i]=0;
	for(int i=0;i<n;i++)	buc[ra1[i]=str[i]]++;
	for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
	for(int i=n-1;i>=0;i--)	su1[--buc[str[i]]]=i;
	for(int i=0;i<n;i++)	cout<<su1[i]<<" ";
	for(int len=1,cnt=1;cnt<n;len*=2,m=cnt)
	{
		cnt=0;
		for(int i=n-len;i<n;i++)	su2[cnt++]=i;
		for(int i=0;i<n;i++)	if(su1[i]>=len)	su2[cnt++]=su1[i]-len;
		for(int i=0;i<n;i++)	tst[i]=ra1[su2[i]];
		
		for(int i=0;i<m;i++)	buc[i]=0;
		for(int i=0;i<n;i++)	buc[ra1[i]]++;
		for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
		for(int i=n-1;i>=0;i--)	su1[--buc[tst[i]]]=su2[i];
		
		tmp=ra1,ra1=su2,su2=tmp;
		ra1[su1[0]]=0;
		cnt=1;
		for(int i=1;i<n;i++)
			if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+len]==su2[su1[i]+len])	ra1[su1[i]]=cnt-1;
			else	ra1[su1[i]]=cnt++;
	}
}
int main()
{
	scanf("%s",str);
	int len;
	len=strlen(str);
	for(int i=len;i<2*len;i++)	str[i]=str[i-len];
	str[2*len]=1;
	str[2*len+1]='\0';
	suffix_array(str,suf,len*2+1,130);
	
	for(int i=0;i<2*len+1;i++)
		if(suf[i]<len)
			putchar(str[suf[i]+len-1]);
}
