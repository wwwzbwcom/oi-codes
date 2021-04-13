#include<algorithm>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
const int maxn=1e6+100;
int n,q;
int sto[maxn];
char str[maxn];
int pos[maxn];
int del[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				Node(){init();}
				void init(){ls=rs=0;	le=re=mni=sum=0;}
				Node *ls,*rs;
				int le,re;
				int mni,sum;
		};
		Node n[maxn*3];
		int nn=0;
	public:
		Node *r;
		void init()
		{
			nn=0;	r=0;
			for(int i=0;i<maxn*3;i++)	n[i].init();
		}
		Node *build(int le,int re)
		{
			Node *u=&n[++nn];
			u->le=le;	u->re=re;
			if(le==re)	u->mni=sto[le],u->sum=1;
			else
			{
				int mid=(le+re)>>1;
				u->ls=build(le,mid);
				u->rs=build(mid+1,re);
				u->mni=min(u->ls->mni,u->rs->mni);
				u->sum=u->ls->sum+u->rs->sum; 
			}
			return u;
		}
		void optera(Node *u,int pos)
		{
			int le=u->le,re=u->re;
			int mid=(le+re)>>1;
			if(le==re)	u->mni=1e9,u->sum=0;
			else
			{
				if(pos<=mid)	optera(u->ls,pos);
				else	optera(u->rs,pos);
				u->mni=min(u->ls->mni,u->rs->mni);
				u->sum=u->ls->sum+u->rs->sum;
			}
		}
		int qrymni(Node *u,int lc,int rc)
		{
			int le=u->le,re=u->re;
			int mid=(le+re)>>1;
			if(le==lc&&re==rc)	return u->mni;
			else
			{
				if(rc<=mid)	return qrymni(u->ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymni(u->rs,lc,rc);
					else	return min(qrymni(u->ls,lc,mid),qrymni(u->rs,mid+1,rc));
				}
			}
		}
		int qrysum(Node *u,int lc,int rc)
		{
			int le=u->le,re=u->re;
			int mid=(le+re)>>1;
			if(le==lc&&re==rc)	return u->sum;
			else
			{
				if(rc<=mid)	return qrysum(u->ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrysum(u->rs,lc,rc);
					else	return qrysum(u->ls,lc,mid)+qrysum(u->rs,mid+1,rc);
				}
			}
		}
}xd;
int workl(int pos)
{
	int l=1,r=pos,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(xd.qrymni(xd.r,mid,pos)>=sto[pos])	ans=mid,r=mid-1;
		else	l=mid+1;
	}
	return xd.qrysum(xd.r,ans,pos);
}
int workr(int pos)
{
	int l=pos,r=n,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(xd.qrymni(xd.r,pos,mid)>=sto[pos])	ans=mid,l=mid+1;
		else	r=mid-1;
	}
	return xd.qrysum(xd.r,pos,ans);
}
int main()
{
//	freopen("ex_A4.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]),pos[sto[i]]=i;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		xd.init();
		xd.r=xd.build(1,n);
		memset(del,0,sizeof del);
		scanf("%s",str);
		int ans=1e9;
		for(int i=1;i<=n;i++)	if(str[i-1]=='0')	del[sto[i]]=1;
		for(int i=1;i<=n;i++)	if(del[i]==1)	ans=min(ans,workl(pos[i])+workr(pos[i])-1),xd.optera(xd.r,pos[i]);
		printf("%d\n",ans);
	}
}
