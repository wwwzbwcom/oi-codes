#include<cstdio>
#include<cstring>
//#include<iostream> 
#include<algorithm>
using namespace std;
const int maxn=2001000;
class HS
{
	public:
		char str[maxn];
		int len;
		long long mul[maxn];
		long long has[maxn];
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
		char str[maxn];
		int len;
		int su1[maxn];
		int *su2,*ra1;
		int po1[maxn],po2[maxn];
		int buc[maxn],tst[maxn];
		SA()
		{
			su2=po1;
			ra1=po2;
		}
		void getsu1()
		{
			int kn=127;
			str[len]='#';
			for(int i=0;i<kn;i++)	buc[i]=0;
			for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
			for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
			for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
			int kc=0;
			for(int p=1;kc<len;p*=2,kn=kc)
			{
				int cnt=0;
				for(int i=len-p;i<len;i++)	su2[cnt++]=i;
				for(int i=0;i<len;i++)	if(su1[i]>=p)	su2[cnt++]=su1[i]-p;
				
				for(int i=0;i<len;i++)	tst[i]=ra1[su2[i]];
				for(int i=0;i<kn;i++)	buc[i]=0;
				for(int i=0;i<len;i++)	buc[tst[i]]++;
				for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
				for(int i=len-1;i>=0;i--)	su1[--buc[tst[i]]]=su2[i];
				
				kc=0;	swap(ra1,su2);	ra1[su1[0]]=0;
				for(int i=1;i<len;i++)
					if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+p]==su2[su1[i]+p])	ra1[su1[i]]=kc;	else	ra1[su1[i]]=++kc;
				++kc;
			}
		}
}sa;
int hei[maxn];
void gethei()
{
	hei[0]=0;
	for(int i=1;i<sa.len;i++)
	{
		int l=0,r=min(sa.len-sa.su1[i-1],sa.len-sa.su1[i]),ans=0;
		while(l<=r)
		{
			int m=(l+r)/2;
			if(hs.getkey(sa.su1[i-1],m)==hs.getkey(sa.su1[i],m))	ans=m,l=m+1;
			else	r=m-1;
		}
		hei[i]=ans;
	}
}
int boo[maxn];
void work(int t,int k)
{
	gethei();
	if(t==0)
	{
		int p=-1;
		for(int i=0;i<sa.len;i++)
		{
			if(k-(sa.len-(sa.su1[i]+hei[i]))>0)	k-=(sa.len-(sa.su1[i]+hei[i]));
			else
			{
				p=i;
				break;
			}
		}
		if(p==-1)	printf("-1\n");
		else	printf("%.*s\n",hei[p]+k,sa.str+sa.su1[p]);
	}
	else
	{
		int p=0;
		for(int i=0;i<sa.len;i++)
		{
		//	if(k-(sa.len-))			
		}
		if(p==-1)	printf("-1\n");
		else;
	}
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	
	scanf("%s",sa.str);
	sa.len=hs.len=strlen(sa.str);
	memcpy(hs.str,sa.str,sizeof sa.str);
	sa.getsu1();
	hs.gethas();
//	for(int i=0;i<sa.len;i++)	cout<<i<<" "<<sa.su1[i]<<endl;
	int t,k;	scanf("%d%d",&t,&k);
	work(t,k); 
}
