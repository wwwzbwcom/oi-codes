#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1000100;
const int mod=998244353;
int n;
int val[maxn];

struct XDS
{
	struct NODE
	{
		int ls,rs;
		int le,re;
		int add[3],sou[3];
	}n[maxn];
	int nn,r;
	int build(int le,int re)
	{
		int u=++nn;
		n[u].le=le;	n[u].re=re;
		n[u].add[0]=n[u].add[1]=0;
		if(le==re)	n[u].ls=n[u].rs=0;
		else
		{
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	void addrng(int u,int lc,int rc,int add,int sou,int mode)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(le==lc&&re==rc)
		{
		//	cout<<le<<"="<<add<<endl;
			n[u].add[mode]=(n[u].add[mode]+add)%mod;
			n[u].sou[mode]=(n[u].sou[mode]+sou)%mod;
		}
		else
		{
			if(rc<=mid)	addrng(n[u].ls,lc,rc,add,sou,mode);
			else
			{
				if(lc>=mid+1)	addrng(n[u].rs,lc,rc,add,sou,mode);
				else
				{
					if(mode==0)
					{
						addrng(n[u].ls,lc,mid,add,sou,mode);
						addrng(n[u].rs,mid+1,rc,(add+(1ll*(mid-le+1)*sou))%mod,sou,mode);
					} 
					if(mode==1)
					{
						addrng(n[u].ls,lc,mid,(add+(1ll*(re-(mid+1)+1)*sou))%mod,sou,mode);
						addrng(n[u].rs,mid+1,rc,add,sou,mode);
					}
					if(mode==2)
					{
						addrng(n[u].ls,lc,mid,add,sou,mode);
						addrng(n[u].rs,mid+1,rc,add,sou,mode);
					}
				}
			}
		}
	}
	int qrypos(int u,int p,int mode)
	{
		int le=n[u].le,re=n[u].re;
		int mid=(le+re)/2;
		if(le==re)	return n[u].add[mode];
		else
		{
			if(p<=mid)
			{
				if(mode==0)	return (qrypos(n[u].ls,p,mode)+1ll*(p-le)*n[u].sou[0]+n[u].add[0])%mod;
				if(mode==1)	return (qrypos(n[u].ls,p,mode)+1ll*(re-p)*n[u].sou[1]+n[u].add[1])%mod;
				if(mode==2) return (qrypos(n[u].ls,p,mode)+n[u].add[2])%mod;
			}
			else
			{
				if(mode==0)	return (qrypos(n[u].rs,p,mode)+1ll*(p-le)*n[u].sou[0]+n[u].add[0])%mod;
				if(mode==1)	return (qrypos(n[u].rs,p,mode)+1ll*(re-p)*n[u].sou[1]+n[u].add[1])%mod;
				if(mode==2)	return (qrypos(n[u].rs,p,mode)+n[u].add[2])%mod;
			}
		}
	}
}xd;
int lef[maxn][21];
int rig[maxn][21];
void build()
{
	for(int i=1;i<=n;i++)
	{
		lef[i][0]=val[i-1];
		for(int j=1;j<=20;j++)
		{
			if(i-(1<<j)>=1)	lef[i][j]=max(lef[i][j-1],lef[i-(1<<(j-1))][j-1]);
			else	lef[i][j]=2e9;
		}
	}
	for(int i=n;i>=1;i--)
	{
		rig[i][0]=val[i+1];
		for(int j=1;j<=20;j++)
		{
			if(i+(1<<j)<=n)	rig[i][j]=max(rig[i][j-1],rig[i+(1<<(j-1))][j-1]);
			else	rig[i][j]=2e9;
		}
	}
}
int findlef(int p,int val)
{
	while(1)
	{
		int flag=0;
		for(int i=20;i>=0;i--)
			if(lef[p][i]<val)
			{
				flag=1;
				p=p-(1<<i);
				break;
			}
		if(flag==0)	return p;
	}
}
int findrig(int p,int val)
{
	while(1)
	{
		int flag=0;
		for(int i=20;i>=0;i--)
			if(rig[p][i]<val)
			{
				flag=1;
				p=p+(1<<i);
				break;
			}
		if(flag==0)	return p;
	}
}
int ans=0;
int sum[maxn];
int main()
{
	scanf("%d",&n);
	xd.r=xd.build(1,n);
//	xd.addrng(xd.r,2,2,19,19,1);
//	for(int i=1;i<=n;i++)	cout<<i<<" "<<xd.qrypos(xd.r,i,1)<<endl;;
	val[0]=2e9;	val[n+1]=2e9;
	for(int i=1;i<=n;i++)	scanf("%d",&val[i]);
	build();
	
	for(int i=1;i<=n;i++)
	{
		int l=i-findlef(i,val[i])+1;
		int r=findrig(i,val[i])-i+1;
		if(r<=l)	swap(l,r);
		
						xd.addrng(xd.r,1  ,l    ,val[i],val[i],0);
		if(l+1<=r)		xd.addrng(xd.r,l+1,r    ,l*val[i],0,2);
		if(r+1<=l+r-1)	xd.addrng(xd.r,r+1,l+r-1,val[i],val[i],1);
	}
	int ans=0;
	for(int i=1;i<=n;i++)	sum[i]=(1ll*xd.qrypos(xd.r,i,0)+xd.qrypos(xd.r,i,1)+xd.qrypos(xd.r,i,2))%mod,ans^=sum[i];
	printf("%d",ans);
}
