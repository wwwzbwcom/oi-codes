#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100100;
int n,k,b,m;
int kc;
int str[maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int mni,pos;
		}n[maxn*3];
		int nn;
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mni=str[le],n[u].pos=le;
			else
			{
				int mid=(le+re)>>1; 
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
				if(n[n[u].ls].mni<=n[n[u].rs].mni)	n[u].pos=n[n[u].ls].pos;
				else	n[u].pos=n[n[u].rs].pos; 
			}
			return u;
		}
		pair<int,int> qrymni(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			if(le==lc&&re==rc)	return make_pair(n[u].pos,n[u].mni);
			else
			{
				if(rc<=mid)	return qrymni(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymni(n[u].rs,lc,rc);
					else
					{
						pair <int,int> lp=qrymni(n[u].ls,lc,mid),rp=qrymni(n[u].rs,mid+1,rc);
						if(lp.second<=rp.second)	return lp;
						else	return rp;
					}
				}
			}
		}
		void optchg(int u,int pos,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			if(le==re)	n[u].mni=val;
			else
			{
				if(pos<=mid)	optchg(n[u].ls,pos,val);
				else	optchg(n[u].rs,pos,val);
				n[u].mni=min(n[n[u].ls].mni,n[n[u].rs].mni);
				if(n[n[u].ls].mni<=n[n[u].rs].mni)	n[u].pos=n[n[u].ls].pos;
				else	n[u].pos=n[n[u].rs].pos;
			}
		}
}xd;
class Ans
{
	public:
		int s[20],sn;
		int c;
		bool operator <(const Ans &in)const
		{
			int lim=min(in.sn,sn);
			for(int i=0;i<lim;i++)
			{
				if(s[i]<in.s[i])	return 1;
				if(s[i]>in.s[i])	return 0;
			}
			return sn<in.sn;
		}
}ans[maxn];
int an,kc;
int us[20],usn;
void dfs(int up,int uc)
{
	if(up!=0)
	{
		memcpy(ans[an].s,us,20*sizeof(int));
		ans[an].sn=usn;
		ans[an].c=uc;
		an++;
	}
	if(up==n)	return;
	
	int mni=1e9;
	for(int i=up+1;i<=n;i++)
	{
		pair <int,int> tmp=xd.qrymni(xd.r,up+1,n);
		int vp=tmp.first;
		int vc=((long long)uc*b+str[vp])%(long long)m;
		
		us[usn++]=str[vp];	xd.optchg(xd.r,vp,1e9);
		dfs(vp,vc);
		us[--usn]=0;
		
		if(kc==k)	return;
	}
	for(int i=up+1;i<=n;i++)	xd.optchg(xd.r,i,str[i]);
}
int main()
{
	scanf("%d%d%d%d",&n,&k,&b,&m);
	xd.r=xd.build(1,n);
	for(int i=1;i<=n;i++)	scanf("%d",&str[i]);
	dfs(0,0);
	sort(ans,ans+an); 
	for(int i=0;i<k;i++)	printf("%d\n",ans[i].c);
}
