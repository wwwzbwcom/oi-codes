#include<algorithm>
//#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=2001000;
struct Suffix_array
{
	char str[maxn];
	int *su2,*ra1;
	int su1[maxn],po1[maxn],po2[maxn];
	int buc[maxn],typ[maxn];
	Suffix_array()
	{
		su2=po1,ra1=po2;
	}
	void getsa()
	{
		int len=strlen(str);
		str[len]='#';
		str[len+1]='\0';
		len++;
		for(int i=0;i<150;i++)	buc[i]=0;
		for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
		for(int i=1;i<150;i++)	buc[i]+=buc[i-1];
		for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
		int kn=0;
		for(int i=1,kc=0;kc<len;i*=2,kn=kc)
		{
			int cnt=0;
			for(int j=len-i;j<len;j++)	su2[cnt++]=j;
			for(int j=0;j<len;j++)	if(su1[j]>=i)	su2[cnt++]=su1[j]-i;
			for(int j=0;j<len;j++)	typ[j]=ra1[su2[j]];
			
			for(int j=0;j<kn;j++)	buc[j]=0;
			for(int j=0;j<len;j++)	buc[typ[j]]++;
			for(int j=1;j<kn;j++)	buc[j]+=buc[j-1];
			for(int j=len-1;j>=0;j--)	su1[--buc[typ[j]]]=su2[j];
			
			swap(ra1,su2);	kc=0;
			ra1[su1[0]]=kc;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j]]&&su2[su1[j-1]+i]==su2[su1[j]+i])	ra1[su1[j]]=kc;	else	ra1[su1[j]]=++kc;
			kc++;
		}
	}
}sa;
struct Externdkmp
{
	char stp[maxn];
	char sts[maxn];
	int nxt[maxn];
	int ext[maxn];
	void getnxt()
	{
		int len=strlen(sts),s=1;
		nxt[0]=len;
		while(nxt[1]<len&&sts[nxt[1]]==sts[nxt[1]+1])	nxt[1]++;
		for(int i=2;i<len;i++)
		{
			int e=s+nxt[s]-1;
			if(i+nxt[i-s]-1<e)	nxt[i]=nxt[i-s];
			else
			{
				if(e-i+1>0)	nxt[i]=e-i+1;	else	nxt[i]=0;
				while(nxt[i]<len&&sts[nxt[i]]==sts[i+nxt[i]])	nxt[i]++;
				s=i;
			}
		}
	}
	void getext()
	{
		int lep=strlen(stp);
		int les=strlen(sts),s=0;
		while(nxt[0]<les&&nxt[0]<lep&&sts[nxt[0]]==stp[nxt[0]])	nxt[0]++;
		for(int i=1;i<lep;i++)
		{
			int e=s+ext[s]-1;
			if(i+nxt[i-s]-1<e)	ext[i]=nxt[i-s];
			else
			{
				if(e-i+1>0)	ext[i]=e-i+1;	else	ext[i]=0;
				while(ext[i]<les&&ext[i]<lep&&sts[ext[i]]==stp[i+ext[i]])	ext[i]++;
				s=i;
			}
		}
	}
}f,b;
int n,m;
char st1[maxn],st2[maxn];
int main()
{
//	freopen("rotate9.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s%s",st1,st2);
	memcpy(sa.str,st2,m);	memcpy(sa.str+m,st2,m+1);
	sa.getsa();
	for(int i=0;i<2*m;i++)	if(sa.su1[i]<m)
	{
		memcpy(f.sts,sa.str+sa.su1[i],m);	f.sts[m]='\0';	memcpy(f.stp,st1,n);	memcpy(f.stp+n,st1,n+1);
		memcpy(b.sts,sa.str+sa.su1[i],m);	b.sts[m]='\0';	memcpy(b.stp,st1,n);	memcpy(b.stp+n,st1,n+1);	reverse(b.sts,b.sts+m);	reverse(b.stp,b.stp+n*2);
		f.getnxt();	f.getext();
		b.getnxt();	b.getext();
		printf("%s\n",f.sts);
		int mni=1e8,p;
		for(int j=0;j<n;j++)
			if(f.ext[j]+b.ext[2*n-(j+m-1)-1]>=m-1)
			{
				if(j<mni)	mni=j,p=j;
				if((n-1)-j<=mni)	mni=(n-1)-j<=mni,p=j;
			}
		for(int j=p;j<p+n;j++)	putchar(f.stp[j]);
		putchar('\n');
		break;
	}
}
