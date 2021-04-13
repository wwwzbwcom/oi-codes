#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
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
class XDS
{
	private:
		class Node
		{
			public:
				int le,re;
				int ls,rs;
				int mni;
		}n[maxn*3];
		int nn;
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mni=hei[le];
			else
			{
				int m=(le+re)/2;
				n[u].ls=build(le,m);
				n[u].rs=build(m+1,re);
				n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
			}
			return u;
		}
		int qrymin(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
		//	cout<<lc<<" "<<lc<<" "<<rc<<endl; 
			if(le==lc&&re==rc)	return n[u].mni;
			else
			{
				if(rc<=mid)	return qrymin(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymin(n[u].rs,lc,rc);
					else	return	min(qrymin(n[u].ls,lc,mid),qrymin(n[u].rs,mid+1,rc));
				}
			}
		}
}xd;
int work()
{
	int ret=-1,p=0,ll=0;
	for(int i=0;i<len;i++)
	{
		if(hei[i]==0)	continue;
		int l,r,fans=0,bans=0;
		l=i+1,r=len-1;
		while(l<=r)
		{
			int m=(l+r)/2;
			if(xd.qrymin(xd.r,i+1,m)>=hei[i])	fans=(m-i),l=m+1;
			else	r=m-1;
		}
		l=0,r=i-1;
		while(l<=r)
		{
			int m=(l+r)/2;
			//if(sa.su1[i]==8452)	printf("%d=%d %d=%d %d\n",l,r,m,i-1,xd.qrymin(xd.r,m,i-1));
			if(xd.qrymin(xd.r,m,i-1)>=hei[i])	bans=(i-m),r=m-1;
			else	l=m+1;
		}
		if(hei[i]*(fans+bans+2)>ret)
		{
			ret=hei[i]*(fans+bans+2);
			p=sa.su1[i];
			ll=hei[i];
		}
	//	if(sa.su1[i]==8452)	printf("%d %d %d %d %d\n",i-(i-1)+1,fans,bans,xd.qrymin(xd.r,i-1,i-1),hei[i]);
	//	printf("%d %d %d\n",hei[i],fans,bans);
	}
	printf("%d\n",ret);
	if(ret!=-1)	printf("%.*s",ll,str+p);
}
int main()
{
	scanf("%s",&str);
	len=strlen(str);
	hs.gethas();
	sa.getsu1();
	gethei();
	xd.r=xd.build(0,len-1);
	work();
}
