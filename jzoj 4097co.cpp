#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2e4+100;
char str[maxn];
int len;
class Hash
{
	public:
		long long mul[maxn];
		long long has[maxn];
		void gethas()
		{
			mul[0]=1;	for(int i=1;i<maxn;i++)	mul[i]=mul[i-1]*127;
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
	private:
		int *su2;
		int po1[maxn],po2[maxn];
		int typ[maxn],buc[maxn];
	public:
		int su1[maxn],*ra1;
		SA()
		{
			su2=po1;	ra1=po2;
		}
		void getsu1()
		{
			for(int i=len;i<maxn;i++)	ra1[i]=-1,su1[i]=-1,su2[i]=-1;
			int kn=127;
			for(int i=0;i<kn;i++)	buc[i]=0;
			for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
			for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
			for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
			int kc=0;
			for(int p=1;kc<len;kn=kc,p*=2)
			{
				int cnt=0;
				for(int i=len-p;i<len;i++)	su2[cnt++]=i;
				for(int i=0;i<len;i++)	if(su1[i]-p>=0)	su2[cnt++]=su1[i]-p;
				
				for(int i=0;i<len;i++)	typ[i]=ra1[su2[i]];
				for(int i=0;i<kn;i++)	buc[i]=0;
				for(int i=0;i<len;i++)	buc[typ[i]]++;
				for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
				for(int i=len-1;i>=0;i--)	su1[--buc[typ[i]]]=su2[i];
				
				kc=0;	swap(ra1,su2);	ra1[su1[0]]=0;
				for(int i=1;i<len;i++)
					if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+p]==su2[su1[i]+p])	ra1[su1[i]]=kc;	else	ra1[su1[i]]=++kc;
				++kc;
				
			//	for(int i=0;i<len;i++)	cout<<su2[i]<<" ";
			//	cout<<"="<<cnt<<endl;
			//	getchar(); 
			}
			str[len]='\0';
		}
}sa;
int hei[maxn];
void gethei()
{
	hei[0]=0;
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
	}
}
int blo[maxn],bn;
int lis[maxn/4][maxn/2];
int lin[maxn];
void work()
{
	int ret=-1,pos,lll;
	for(int p=len/2;p>=1;p--)
	{
		int flag=0;	bn=0;
		memset(lin,0,sizeof lin);
		for(int i=0;i<len;i++)
		{
			if(flag==0)
			{
				if(hei[i]>=p)	flag=1,blo[sa.su1[i-1]]=++bn;
				else	blo[sa.su1[i]]=0;
			}
			if(flag)
			{
				if(hei[i]<p)	flag=0,blo[sa.su1[i]]=0;
				else	blo[sa.su1[i]]=bn;
			}
		}
		//cout<<bn<<endl;
		for(int i=0;i<len;i++)
		{
			if(blo[i]!=0)	lis[blo[i]][lin[blo[i]]++]=i;
		}
		for(int i=1;i<=bn;i++)
		{
			int las=-1,cnt=0;
			for(int j=0;j<lin[i];j++)
				if(lis[i][j]>las)
				{
					las=lis[i][j]+p-1;
					cnt++;
				}
			if(cnt*p>ret)
			{
				ret=cnt*p;
				pos=lis[i][0];
				lll=p;
			}
			else
			{
				if(cnt*p==ret)
				{
					if(lll>p&&sa.ra1[pos]>=sa.ra1[lis[i][0]])
					{
						ret=cnt*p;
						pos=lis[i][0];
						lll=p;	
					}	
				}
			}
		}
	}
	printf("%d\n",ret);
	if(ret!=-1)	printf("%.*s",lll,str+pos);
}
int main()
{
	scanf("%s",&str);
	len=strlen(str);
	hs.gethas();
	sa.getsu1();
	gethei();
	work();
}
