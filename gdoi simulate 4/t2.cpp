#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200100;
const int oo=1e8;
struct Suffixarray
{
	char str[maxn];
	int su1[maxn],su2[maxn],ra1[maxn];
	int buc[maxn],typ[maxn];
	void getsa()
	{
		int len=strlen(str),kn=150;
		str[len]='#';	len++;	str[len]='\0';
		for(int i=0;i<kn;i++)	buc[i]=0;
		for(int i=0;i<len;i++)	buc[ra1[i]=str[i]]++;
		for(int i=1;i<kn;i++)	buc[i]+=buc[i-1];
		for(int i=len-1;i>=0;i--)	su1[--buc[str[i]]]=i;
		
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
			
			kc=0;	swap(ra1,su2);
			ra1[su1[0]]=0;
			for(int j=1;j<len;j++)	if(su2[su1[j-1]]==su2[su1[j]]&&su2[su1[j-1]+i]==su2[su1[j]+i])	ra1[su1[j]]=kc;	else	ra1[su1[j]]=++kc;
			kc++;
		}
	}
}sa;
struct XDS
{
	struct Node
	{
		Node()
		{
			ls=rs=NULL;
			le=re=0;
			set=0;
		}
		Node *ls,*rs;
		int le,re;
		int set,inc;
	};
	Node *r;
	Node* build(int le,int re)
	{
		Node *u=new Node;
		u->le=le;	u->re=re;
		u->set=oo;	u->inc=oo;
		if(le!=re)
		{
			int mid=(le+re)/2;
			u->ls=build(le,mid);
			u->rs=build(mid+1,re); 
		}
		return u;
	}
	void set(Node *u,int lc,int rc,int val)
	{
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
	//	cout<<le<<" "<<re<<" "<<lc<<" "<<rc<<endl; 
		if(le==lc&&re==rc)	u->set=min(u->set,val);
		else
		{
			if(rc<=mid)	set(u->ls,lc,rc,val);
			else
			{
				if(lc>=mid+1)	set(u->rs,lc,rc,val);
				else	set(u->ls,lc,mid,val),set(u->rs,mid+1,rc,val);
			}
		}
	}
	void inc(Node *u,int lc,int rc,int val)
	{
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
		if(le==lc&&re==rc)	u->inc=min(u->inc,val);
		else
		{
			if(rc<=mid)	inc(u->ls,lc,rc,val);
			else
			{
				if(lc>=mid+1)	inc(u->rs,lc,rc,val);
				else	inc(u->ls,lc,mid,val),inc(u->rs,mid+1,rc,val+(mid-lc+1));
			}
		}
	}
	int query(Node *u,int p)
	{
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
		if(le==re)	return min(u->set,u->inc);
		else
		{
		//	cout<<u->inc<<"~"<<p-le+1<<"~"<<u->set<<endl;
			if(p<=mid)	return min(min(query(u->ls,p),u->set),u->inc+(p-le));
			else	return min(min(query(u->rs,p),u->set),u->inc+(p-le));
		}
	}
}xds;
struct Hash
{
	char str[maxn];
	long long mul[maxn];
	long long has[maxn];
	long long rev[maxn];
	long long mod;
	Hash()
	{
		mod=1000000007;
	}
	void init()
	{
		int len=strlen(str+1);
		mul[0]=1;	for(int i=1;i<=len;i++)	mul[i]=(mul[i-1]*130)%mod;
		rev[0]=1;	for(int i=1;i<=len;i++)	rev[i]=(rev[i-1]*515384619)%mod;
		for(int i=1;i<=len;i++)	has[i]=(has[i-1]+mul[i]*str[i])%mod;
	}
	long long substr(int s,int l)
	{
		return (((has[s+l-1]-has[s-1])%mod+mod)%mod*rev[s-1])%mod;
	}
}hs;
int main()
{
//	freopen("istring2.in","r",stdin);
//	freopen("t2.out","w",stdout);
	scanf("%s",sa.str);
	int len=strlen(sa.str);
	memcpy(hs.str+1,sa.str,len);
	hs.init();
//	cout<<hs.substr(1,1)<<" "<<hs.substr(2,1)<<endl;
	sa.getsa();
	int l=0;
	len=strlen(sa.str);
	xds.r=xds.build(0,len);
	for(int i=0;i<len-1;i++)
	{
		l=max(l,0);
	//	l=0;

		int p=sa.ra1[i];
	//	if(i>=15&&i<=30)	cout<<i<<" "<<l<<endl,cout<<i<<" "<<l<<" "<<sa.str[i+l]<<" "<<sa.str[sa.su1[p-1]+l]<<" "<<sa.str[sa.su1[p+1]+l]<<endl;
		int l1=l,l2=l;
		if(p-1>=0 &&hs.substr(i+1,l+1)==hs.substr(sa.su1[p-1]+1,l+1))	while(i+l1<len&&sa.su1[p-1]+l1<len&&sa.str[i+l1]==sa.str[sa.su1[p-1]+l1])	l1++;
		if(p+1<len&&hs.substr(i+1,l+1)==hs.substr(sa.su1[p+1]+1,l+1))	while(i+l2<len&&sa.su1[p+1]+l2<len&&sa.str[i+l2]==sa.str[sa.su1[p+1]+l2])	l2++;
		l=max(l1,l2);
		if(i+l<len-1)
		{
			xds.set(xds.r,i,i+l,l+1);
			if(i+l+1<len-1)	xds.inc(xds.r,i+l+1,len-1,l+2);
		}
	//	cout<<i<<" "<<l<<endl;
		
		l--;
	//	if(i>=15&&i<=30)	cout<<i<<" "<<l+1<<endl,cout<<i<<" "<<l<<" "<<sa.str[i+l]<<" "<<sa.str[sa.su1[p-1]+l]<<" "<<sa.str[sa.su1[p+1]+l]<<endl;
	//	if(i==17||i==18)	printf("%s\n",sa.str+i),printf("%s\n",sa.str+sa.su1[p-1]),printf("%s\n",sa.str+sa.su1[p+1]);
		if(l>=0&&sa.str[i+l]!=sa.str[sa.su1[p-1]+l]&&sa.str[i+l]!=sa.str[sa.su1[p+1]+l])	cout<<i<<endl;
	}
//	return 0;
	for(int i=0;i<len-1;i++)	printf("%d\n",xds.query(xds.r,i));
//	printf("%d",len);
}
