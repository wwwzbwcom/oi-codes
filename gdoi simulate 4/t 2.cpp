#include<iostream>
using namespace std;
struct Suffixarray
{
	char str[maxn];
	int su1[maxn],su2[maxn],ra1[maxn];
	int buc[maxn],typ[maxn];
	void getsa()
	{
		int len=strlen(len),kn=150;
		str[len]='#';	len++;	str[len]='\0';
		for(int i=0;i<kn;i++)	buc[i]=0;
		for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
		for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
		
		for(int i=1,kc=0;kc<len;i*=2,kn=kc)
		{
			int cnt=0;
			for(int j=len-i;j<len;j++)	su2[cnt++]=j;
			for(int j=0;j<len;j++)	if(su1[j]>=i)	su2[cnt++]=su1[j]-i;
			
			for(int j=0;j<len;j++)	tst[j]=ra1[su2[j]];
			for(int j=0;j<kn;j++)	buc[j]=0;
			for(int j=0;j<len;j++)	buc[tst[j]]++;
			for(int j=len-1;j>=0;j--)	su1[--buc[tst[i]]]=su2[j];
			
			kc=0;	swap(ra1,su2);
			ra1[su1[0]]=0;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j]]&&su2[su1[j-1]+i]==su2[su1[j-1]+i])	ra1[j]=kc;	else	ra1[j]=++kc;
			kc++;
		}
	}
}sa;
int main()
{
	cin>>sa.str;
	int len=strlen(sa.str);
	for(int i=0;i<len;i++)	cout<<i<<" "<<sa.su1[i]<<endl;
}
