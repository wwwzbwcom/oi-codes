#include<queue>
#include<cstdio>
using namespace std;
const int maxn=500100;
int val[maxn];
int sum[maxn];
int n,k,llim,rlim;
long long ans;
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int mxa,pos;
		}n[maxn*3];
		int nn;
		void pull(int u)
		{
			if(n[n[u].ls].mxa>=n[n[u].rs].mxa)
			{
				n[u].mxa=n[n[u].ls].mxa;
				n[u].pos=n[n[u].ls].pos;
			}
			else
			{
				n[u].mxa=n[n[u].rs].mxa;
				n[u].pos=n[n[u].rs].pos;
			}
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le==re)	n[u].mxa=sum[le],n[u].pos=le;
			else
			{
				int mid=(le+re)>>1;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			}
			return u;
		}
		int qrymxa(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
		//	cout<<le<<" "<<re<<" "<<lc<<" "<<rc<<endl;
		//	getchar();
			if(le==lc&&re==rc)	return n[u].pos;
			else
			{
				int mid=(le+re)>>1;
				if(rc<=mid)	return qrymxa(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return qrymxa(n[u].rs,lc,rc);
					else
					{
						int p1=qrymxa(n[u].ls,lc,mid),p2=qrymxa(n[u].rs,mid+1,rc);
						if(sum[p1]>=sum[p2])	return p1;
						else	return p2;
					}
				}
			}
		}
}xd;
class CON
{
	public:
		CON(int pi,int li,int ri)
		{
			p=pi;	l=li;	r=ri;
			pos=xd.qrymxa(xd.r,li,ri);
			val=sum[pos]-sum[p-1];
		}
		int p,l,r,pos,val;
		bool operator <(const CON &in)const
		{
			return val<in.val;
		}
};
int main()
{
	scanf("%d%d%d%d",&n,&k,&llim,&rlim);
	for(int i=1;i<=n;i++)	scanf("%d",&val[i]);
	for(int i=1;i<=n;i++)	sum[i]=sum[i-1]+val[i];
	xd.r=xd.build(1,n);
	priority_queue <CON> que;
	for(int i=1;i<=n;i++)	if(i+llim-1<=n)	que.push(CON(i,i+llim-1,min(n,i+rlim-1)));
	for(int i=1;i<=k;i++)
	{
		CON u=que.top();	que.pop();
		ans+=u.val;	//fcout<<u.val<<"="<<endl;
		if(u.pos-1>=u.l)	que.push(CON(u.p,u.l,u.pos-1));
		if(u.pos+1<=u.r)	que.push(CON(u.p,u.pos+1,u.r));
	}
	printf("%lld",ans); 
}
