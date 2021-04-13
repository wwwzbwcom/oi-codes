#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=50100;
char str[maxn];
int len;
int n;
class Hash
{
	public:
		long long has[maxn];
		long long mul[maxn];
		void gethas()
		{
			mul[0]=1;	for(int i=1;i<=len;i++)	mul[i]=mul[i-1]*127;
			has[0]=0;	for(int i=1;i<=len;i++)	has[i]=has[i-1]*127+str[i-1];
		}
		long long getkey(int p,int l)
		{
			p++;
			return has[p+l-1]-has[p-1]*mul[l];
		}
}hs;
class SA
{
	public:
		int su1[maxn];
		int *su2,*ra1;
		int po1[maxn],po2[maxn];
		int buc[maxn],typ[maxn];
		SA()
		{
			su2=po1;	ra1=po2;
			for(int i=0;i<maxn;i++)	su2[i]=-1;
		}
		void getsu1()
		{
			int kn=127;
			for(int i=0;i<kn;i++)	buc[i]=0;
			for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
			for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
			for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
			str[len]='#';
			for(int p=1,kc=0;kc<len;p*=2,kn=kc)
			{
				int cnt=0;
				for(int i=len-p;i<len;i++)	su2[cnt++]=i;
				for(int i=0;i<len;i++)	if(su1[i]>=p)	su2[cnt++]=su1[i]-p;
				
				for(int i=0;i<len;i++)	typ[i]=ra1[su2[i]];
				for(int i=0;i<kn;i++)	buc[i]=0;
				for(int i=0;i<len;i++)	buc[typ[i]]++;
				for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
				for(int i=len-1;i>=0;i--)	su1[--buc[typ[i]]]=su2[i];
				
				//for(int i=0;i<len;i++)	cout<<i<<"="<<su1[i]<<endl;
				
				kc=0;	swap(su2,ra1);	ra1[su1[0]]=0;
				for(int i=1;i<len;i++)
					if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+p]==su2[su1[i]+p])	ra1[su1[i]]=kc;
					else	ra1[su1[i]]=++kc;
				
				++kc;
			}
		}
}sa;
int hei[maxn],num[maxn];
void gethei()
{
	hei[0]=0;
	num[0]=len-sa.su1[0]-hei[0];
	for(int i=1;i<len;i++)
	{
		int l=0,r=min(len-sa.su1[i-1],len-sa.su1[i]),ans=0;
		while(l<=r)
		{
			int m=(l+r)/2;
			if(hs.getkey(sa.su1[i-1],m)==hs.getkey(sa.su1[i],m))	ans=m,l=m+1;
			else	r=m-1;
		}
		hei[i]=ans;
		num[i]=num[i-1]+(len-sa.su1[i]-hei[i]);
	}
	//for(int i=0;i<len;i++)	cout<<i<<" "<<sa.su1[i]<<" "<<hei[i]<<"="<<num[i]<<endl;
}
void query(int k)
{
	int l=0,r=len-1,ans=0;
	while(l<=r)
	{
		int m=(l+r)/2;
		if(num[m]>=k)	 ans=m,r=m-1;
		else	l=m+1;
	}
	//printf("%d %d\n",hei[ans]+(k-num[ans-1]),sa.su1[ans]);
	if(sa.su1[ans]+hei[ans]+(k-num[ans-1])>len)	printf("-1\n");
	else	printf("%.*s\n",hei[ans]+(k-num[ans-1]),str+sa.su1[ans]);
}
int main()
{
	scanf("%s",str);
	len=strlen(str);
	hs.gethas();
	sa.getsu1();
	gethei();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int q;	scanf("%d",&q);
		query(q);
	}
} 
