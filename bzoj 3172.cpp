#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=500100;
struct Suffix_array
{
	char str[maxn];
	int su1[maxn],su2[maxn];
	int ra1[maxn],ra2[maxn];
	int buc[maxn],tst[maxn];
	bool compare(int p1,int p2,int len)
	{
		for(int i=0;i<len;i++)	if(str[p1+i]!=str[p2+i])	return 0;
		return 1;
	}
	void get_sa(int len,int kin)
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
			
			kic=0;	swap(su2,ra1);
			ra1[su1[0]]=0;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j]]&&su2[su1[j-1]+i]==su2[su1[j]+i])	ra1[su1[j]]=kic;	else	ra1[su1[j]]=++kic;
			kic++;
		}
	}
}sa;
int idx[maxn];
int len[maxn];
int main()
{
	int n,las=0;	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		idx[i]=las;
		scanf("%s",sa.str+las);
		len[i]=strlen(sa.str)-las; 
		las=strlen(sa.str);
		sa.str[las]='#';
		sa.str[las+1]='\0';
		las=strlen(sa.str);
	}
	sa.str[las-1]='$';
	sa.get_sa(las,150);
	for(int i=0;i<n;i++)
	{
		int pos=sa.ra1[idx[i]],ans=0;
		int l=0,r=pos,t;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(sa.compare(sa.su1[mid],sa.su1[pos],len[i]))	t=mid,r=mid-1;
			else	l=mid+1;	
		}
		t=pos-t;
		ans+=t;
		l=pos,r=las-1,t;
		while(l<=r)
		{		
			int mid=(l+r)/2;
			if(sa.compare(sa.su1[mid],sa.su1[pos],len[i]))	t=mid,l=mid+1;
			else	r=mid-1;
		}
		t=t-pos;
		ans+=t;
		ans++;
		printf("%d\n",ans);
	}
}
