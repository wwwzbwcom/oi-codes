#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int maxn=100100;
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int cnt[27];
		}n[maxn*3];
		int nn;
		inline void pull(int u)
		{
			if(n[u].ls!=0)
			for(int i=0;i<27;i++)	n[u].cnt[i]=n[n[u].ls].cnt[i]+n[n[u].rs].cnt[i];
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			memset(n[u].cnt,0,sizeof n[u].cnt);
			if(le==re)	n[u].ls=n[u].rs=0;
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
			}
			return u;
		}
		void optchg(int u,int pos,int col)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2; 
			if(le==re)
			{
				memset(n[u].cnt,0,sizeof n[u].cnt);
				if(col!=0)
				{
					n[u].cnt[0]=1;
					n[u].cnt[col]=1;
				}
			}
			else
			{
				if(pos<=mid)	optchg(n[u].ls,pos,col);
				else	optchg(n[u].rs,pos,col);
				pull(u);
			}
		}
		int qrysum(int u,int lc,int rc,int mod)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2; 
		//	cout<<le<<"="<<re<<" "<<lc<<"="<<rc<<endl;
			if(le==lc&&re==rc)
			{
			//	cout<<le<<" "<<re<<" "<<n[u].cnt[mod]<<endl;
				return n[u].cnt[mod];
			}
			else
			{
				if(rc<=mid)	return qrysum(n[u].ls,lc,rc,mod);
				else
				{
					if(lc>=mid+1)	return qrysum(n[u].rs,lc,rc,mod);
					else	return qrysum(n[u].ls,lc,mid,mod)+qrysum(n[u].rs,mid+1,rc,mod);
				}
			}
		}
		int qrylab(int u,int pos)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)
			{
				for(int i=1;i<=26;i++)	if(n[u].cnt[i]>0)	return i;
			}
			else
			{
				if(pos<=mid)	return qrylab(n[u].ls,pos);
				else	return qrylab(n[u].rs,pos);
			}
		}
}xd;
int n;
int top;
void insert(int col)
{
	top++;
	xd.optchg(xd.r,top,col);
}
void erase(int k)
{
	int l=1,r=top,ans=1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(xd.qrysum(xd.r,1,mid,0)>=k)	ans=mid,r=mid-1;
		else	l=mid+1;
	}
	xd.optchg(xd.r,ans,0);
}
void querycol(int k,int col)
{
	int l=1,r=top,ans=1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(xd.qrysum(xd.r,1,mid,col)>=k)	ans=mid,r=mid-1;
		else	l=mid+1;
	}
	printf("%d\n",xd.qrysum(xd.r,1,ans,0));
}
void queryall(int k)
{
	int l=1,r=top,ans=1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(xd.qrysum(xd.r,1,mid,0)>=k)	ans=mid,r=mid-1;
		else	l=mid+1;
	}
	int p=xd.qrylab(xd.r,ans);
	printf("%c\n",'a'+p-1);
}
int main()
{
	scanf("%d",&n);
	xd.r=xd.build(1,1e5);
	for(int i=0;i<n;i++)
	{
		char cmd[5],c[5];
		int k;
		scanf("%s",cmd); 
		if(cmd[0]=='p')	scanf("%s",c),		insert(c[0]-'a'+1);
		if(cmd[0]=='r')	scanf("%d",&k),		erase(k);
		if(cmd[0]=='q')	scanf("%d%s",&k,c),	querycol(k,c[0]-'a'+1);
		if(cmd[0]=='w')	scanf("%d",&k),		queryall(k);
	}
}
