//#include<iostream>
#include<algorithm> 
#include<cstring>
#include<cstdio>
using namespace std;
const long long maxn=100100;
long long sum[maxn*2],val[maxn*2];
long long idx[maxn],lis[maxn],ln;
long long n;
struct XDS
{
	struct NODE
	{
		long long ls,rs;
		long long le,re;
		long long mxa;
		long long va1,va2;
	}n[maxn*6];
	struct RET
	{
		RET(long long va1i,long long va2i,long long mxai)
		{
			va1=va1i;
			va2=va2i;
			mxa=mxai;
		}
		long long va1,va2,mxa;
	};
	long long nn,r;
	void pull(long long u)
	{
		long long ls=n[u].ls,rs=n[u].rs;
		n[u].va1=max(n[ls].va1,n[rs].va1);
		n[u].va2=max(n[ls].va2,n[rs].va2);
		n[u].mxa=max(n[ls].mxa,n[rs].mxa);
		n[u].mxa=max(n[u].mxa,max(n[ls].va1+n[rs].va2,n[ls].va2+n[rs].va1));
	}
	long long build(long long le,long long re)
	{
		long long u=++nn;
		n[u].le=le;	n[u].re=re;
		if(le==re)
		{
			n[u].va1=-sum[le]+val[le];	n[u].va2=sum[le]+val[le];
		//	cout<<n[u].va1<<"=="<<n[u].va2<<endl;
			n[u].mxa=-1;
		}
		else
		{
			long long mid=(le+re)>>1;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		//	cout<<n[u].va1<<" "<<n[u].va2<<endl;
			pull(u);
		}
		return u;
	}
	RET merge(RET const &a,RET const &b)
	{
		RET ans(0,0,0);
		ans.va1=max(a.va1,b.va1);
		ans.va2=max(a.va2,b.va2);
		ans.mxa=max(a.mxa,b.mxa);
		ans.mxa=max(ans.mxa,max(a.va1+b.va2,a.va2+b.va1));
		return ans;
	}
	RET qryrng(long long u,long long lc,long long rc)
	{
		long long le=n[u].le,re=n[u].re;
		long long mid=(le+re)>>1;
	//	cout<<le<<" "<<re<<" "<<lc<<" "<<rc<<endl;
	//	getchar();
		if(le==lc&&re==rc)	return RET(n[u].va1,n[u].va2,n[u].mxa);
		else
		{
			if(rc<=mid)	return qryrng(n[u].ls,lc,rc);
			else
			{
				if(lc>=mid+1)	return qryrng(n[u].rs,lc,rc);
				else	return merge(qryrng(n[u].ls,lc,mid),qryrng(n[u].rs,mid+1,rc));
			}
		}
	}
}xd;
struct CACTUS
{
	struct EDGE
	{
		long long u,v,c;
		long long nxt;
	}e[maxn*2];
	long long pre[maxn],en;
	long long vis[maxn];
	long long dis[maxn],rad[maxn];
	CACTUS()
	{
		memset(pre,-1,sizeof pre);
	}
	addedge(long long u,long long v,long long c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
	}
	long long dfscir(long long u,long long f)
	{
		if(vis[u]==1)	return u;
		vis[u]=1;
		for(long long i=pre[u];i!=-1;i=e[i].nxt)
		{
			long long v=e[i].v,c=e[i].c;
			if(v!=f)
			{
				long long t=dfscir(v,u);
				if(t>0)
				{
					ln++;
					sum[ln]=c;
					lis[ln]=u;
					idx[u]=ln;
					if(u==t)	return -1;	else	return t;
				}
				if(t==-1)	return -1;
			}
		}
		return 0;
	}
	void dfsdis(long long u,long long f)
	{
	//	cout<<u<<endl;
		long long fmx=0,smx=0;
		for(long long i=pre[u];i!=-1;i=e[i].nxt)
		{
			long long v=e[i].v,c=e[i].c;
			if(v!=f&&idx[v]==0)
			{
				dfsdis(v,u);
				rad[u]=max(rad[u],rad[v]);
				if(dis[v]+c>fmx)	smx=fmx,fmx=dis[v]+c;
				else	if(dis[v]+c>smx)	smx=dis[v]+c;
			}
		}
		dis[u]=fmx;
		rad[u]=max(rad[u],fmx+smx);
	}
	long long work()
	{
		long long ans=0,cur=1e16;
		dfscir(1,0);
	//	for(long long i=1;i<=n;i++)	cout<<i<<" "<<idx[i]<<endl;
	//	cout<<"==========="<<endl;
		for(long long u=1;u<=n;u++)	if(idx[u]!=0)	dfsdis(u,0),ans=max(ans,rad[u]),val[idx[u]]=dis[u];
		for(long long i=ln+1;i<=ln+ln;i++)	val[i]=val[i-ln],sum[i]=sum[i-ln];
		sum[1]=0;
		for(long long i=1;i<=ln+ln;i++)	sum[i]+=sum[i-1];
	//	for(long long i=1;i<=ln+ln;i++)	cout<<i<<" "<<sum[i]<<" "<<val[i]<<endl;
	//	cout<<"==========="<<endl;
		xd.r=xd.build(1,ln*2);
		for(long long i=1;i<=ln;i++)	cur=min(cur,xd.qryrng(xd.r,i,i+ln-1).mxa);//,cout<<i<<" "<<xd.qryrng(xd.r,i,i+ln-1).mxa<<endl;
		return max(ans,cur);
	}
}ca;
int main()
{
	scanf("%d",&n);
	for(long long i=1;i<=n;i++)
	{
		long long u,v,c;	scanf("%d%d%d",&u,&v,&c);
		ca.addedge(u,v,c);
	}
	printf("%.1lf\n",ca.work()/2.0);
}
