#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=2000100;
struct Suffix_array
{
	int str[maxn];
	int su1[maxn],su2[maxn];
	int ra1[maxn];
	int buc[maxn],tst[maxn];
	void build(int len,int kin)
	{
		for(int i=0;i<kin;i++)	buc[i]=0;
		for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
		for(int i=1;i<kin;i++)	buc[i]+=buc[i-1];
		for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
		
		for(int i=1,kic=0;kic<len;i*=2,kin=kic)
		{
			int cnt=0;
			for(int j=len-i;j<len;j++)	su2[cnt++]=j;
			for(int j=0;j<len;j++)	if(su1[j]>=i)	su2[cnt++]=su1[j]-i;
			for(int j=0;j<len;j++)	tst[j]=ra1[su2[j]];
			
			for(int j=0;j<kin;j++)	buc[j]=0;
			for(int j=0;j<len;j++)	buc[tst[j]]++;
			for(int j=1;j<kin;j++)	buc[j]+=buc[j-1];
			for(int j=len-1;j>=0;j--)	su1[--buc[tst[j]]]=su2[j];
			
			kic=0;	swap(ra1,su2);
			ra1[su1[0]]=0;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j]]&&su2[su1[j-1]+i]==su2[su1[j]+i])	ra1[su1[j]]=kic;	else	ra1[su1[j]]=++kic;
			kic++;
		}
	}
}sa;
int ale,ble;
int acu,bcu;
int ast[maxn],bst[maxn];
int ans[maxn],ac;
int main()
{
	scanf("%d",&ale);
	for(int i=0;i<ale;i++)	scanf("%d",&ast[i]);
	scanf("%d",&ble);
	for(int i=0;i<ble;i++)	scanf("%d",&bst[i]);
	
	for(int i=0;i<ale;i++)	sa.str[i]=ast[i];
	sa.str[ale]=1099;
	for(int i=ale+1;i<ale+ble+1;i++)	sa.str[i]=bst[i-ale-1];
	
	sa.str[ale+ble+1]=1099;
	
	sa.build(ale+ble+1,1100);
	for(int i=0;i<ale+ble;i++)
	{
		if(acu>=ale)	ans[ac++]=bst[bcu++];
		else
		{
			if(bcu>=ble)	ans[ac++]=ast[acu++];
			else
			{
				if(sa.ra1[acu]<sa.ra1[ale+1+bcu])	ans[ac++]=ast[acu++];
				else	ans[ac++]=bst[bcu++];
			}
		}
	}
	
	for(int i=0;i<ac;i++)	printf("%d ",ans[i]);
}
