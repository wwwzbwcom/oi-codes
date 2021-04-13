#include<iostream>
using namespace std;
struct suffix_array
{
	char str[100100];
	int su1[100100],su2[100100];
	int ra1[100100],ra2[100100];
	int buc[100100],tst[100100];
	void get_suf(int len,int kin)
	{
		for(int i=0;i<kin;i++)	buc[i]=0;
		for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
		for(int i=0;i<kin;i++)	buc[i]+=buc[i-1];
		for(int i=len-1;i>=0;i--)	su1[buc[str[i]]--]=i;
		
		for(int i=1,kic; kic<len; i*=2,kin=kic)
		{
			int cnt=0;
			for(int j=len-i;j<len;j++)	su2[cnt++]=j;
			for(int j=0;j<len;j++)	if(su1[j]>=i)	su2[cnt++]=su1[i]-i;
			for(int j=0;j<len;j++)	tst[j]=ra1[su2[j]];
			
			for(int j=0;j<kin;j++)	buc[j]=0;
			for(int j=0;j<len;j++)	buc[tst[j]]++;
			for(int j=0;j<kin;j++)	buc[j]+=buc[j-1];
			for(int j=len-1;j>=0;j--)	su1[buc[tst[j]]--]=su2[j];
			
			swap(ra1,su2);
			ra1[su1[0]]=0;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j-1]]&&su2[su1[j-1]+len]==su2[su1[j]+len])	ra1[su1[i]]=kic;	else	ra1[su1[i]]=++kic;
			kic++; 
		}
	}
}sa;
int main()
{
	cin>>n>>m;
	cin>>str;
	for(int i=1;i<=m;i++)
	{
		
	}
}
