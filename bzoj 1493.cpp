#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=500500;
int n,c,q;
int mov=0,rev=0;
int col[maxn];
int idx(int pos)
{
	cout<<((pos-mov-1)%n+n)%n+1<<" "<<(n-pos+1)%n+1<<endl;
	if(rev)	pos=(n-pos+1)%n+1;
	return	((pos-mov-1)%n+n)%n+1;
	if(rev==0)	return	((pos-mov-1)%n+n)%n+1;
	else	return (n-(((pos-mov-1)%n+n)%n+1)+2)%n;
}
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int set;
				int lc,rc,cnt;
		}n[maxn*3];
		int nn;
		void push(int u)
		{
			if(n[u].set!=-1)
			{
				if(n[u].ls!=0)
				{
					n[n[u].ls].set=n[u].set;
					n[n[u].rs].set=n[u].set;
				}
				n[u].lc=n[u].rc=n[u].set;
				n[u].cnt=1;
				n[u].set=-1;	
			}	
		}
		void pull(int u)
		{
			if(n[u].ls!=0)
			{
				int ls=n[u].ls,rs=n[u].rs;
				int llc,lrc,lcn,rlc,rrc,rcn;
				if(n[ls].set==-1)	llc=n[ls].lc,lrc=n[ls].rc,lcn=n[ls].cnt;	else	llc=lrc=n[ls].set,lcn=1;
				if(n[rs].set==-1)	rlc=n[rs].lc,rrc=n[rs].rc,rcn=n[rs].cnt;	else	rlc=rrc=n[rs].set,rcn=1;
				
			//	cout<<n[u].le<<" "<<n[u].re<<" "<<llc<<" "<<rrc<<endl;
				n[u].lc=llc;
				n[u].rc=rrc;
				n[u].cnt=lcn+rcn;
			//	cout<<n[u].le<<"="<<n[u].re<<" "<<lcn<<"="<<rcn<<" "<<lrc<<"="<<rlc<<endl;
				if(lrc==rlc)	n[u].cnt--;
			}
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn; 
			n[u].le=le;	n[u].re=re;
			n[u].set=-1;
			if(le==re)	n[u].lc=n[u].rc=col[le],n[u].cnt=1;
			else
			{
				int mid=(le+re)>>1;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
				pull(u);
			}
			return u;
		}
		int qrylef()
		{
			if(n[r].set==-1)	return n[r].lc;
			else	return n[r].set;
		}
		int qryrig()
		{
			if(n[r].set==-1)	return n[r].rc;
			else	return n[r].set;
		}
		int qrypos(int u,int pos)
		{
			int le=n[u].le,re=n[u].re;
			if(le==re)
			{
				if(n[u].set==-1)	return n[u].lc;
				else	return n[u].set;
			}
			else
			{
				push(u);
				int mid=(le+re)>>1,ret=0;
				if(pos<=mid)	ret=qrypos(n[u].ls,pos);
				else	ret=qrypos(n[u].rs,pos);
				pull(u);
				return ret;
			}
		}
		int qryrng(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1,ret=0;
			if(le==lc&&re==rc)
			{
			//	cout<<le<<" "<<re<<" "<<n[u].cnt<<endl;
				if(n[u].set==-1)	return n[u].cnt;
				else	return 1;
			}
			else
			{
				push(u);
				if(rc<=mid)	ret=qryrng(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	ret=qryrng(n[u].rs,lc,rc);
					else
					{
						ret=qryrng(n[u].ls,lc,mid)+qryrng(n[u].rs,mid+1,rc);
						int lrc,rlc;
						if(n[n[u].ls].set==-1)	lrc=n[n[u].ls].rc;	else	lrc=n[n[u].ls].set;
						if(n[n[u].rs].set==-1)	rlc=n[n[u].rs].lc;	else	rlc=n[n[u].rs].set;
					//	cout<<n[n[u].ls].set<<"==="<<n[n[u].rs].set<<" "<<lrc<<"==="<<rlc<<endl;
						if(lrc==rlc)	ret--;
						return ret;
					}
				}
				pull(u);
				return ret;
			}
		}
		void optrng(int u,int lc,int rc,int col)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)>>1;
			if(le==lc&&re==rc)	n[u].set=col;
			else
			{
				push(u);
				if(rc<=mid)	optrng(n[u].ls,lc,rc,col);
				else
				{
					if(lc>=mid+1)	optrng(n[u].rs,lc,rc,col);
					else	optrng(n[u].ls,lc,mid,col),optrng(n[u].rs,mid+1,rc,col);
				}
				pull(u);
			}
		}
}xd;
void rotate(int x)
{
	if(rev==0)	mov+=x; 
	else	mov-=x;
	mov=(mov%n+n)%n;
}
void flip()
{
	rev^=1;
}
void swp(int l,int r)
{
	l=idx(l);	r=idx(r);
	int lv=xd.qrypos(xd.r,l),rv=xd.qrypos(xd.r,r);
	xd.optrng(xd.r,l,l,rv);	xd.optrng(xd.r,r,r,lv);
}
void paint(int lef,int rig,int col)
{
	lef=idx(lef),rig=idx(rig);
	if(rev)	swap(lef,rig);
	//cout<<lef<<"="<<rig<<endl;
	if(lef<=rig)	xd.optrng(xd.r,lef,rig,col);
	else	xd.optrng(xd.r,lef,n,col),xd.optrng(xd.r,1,rig,col);
}
int count()
{
	int ret=xd.qryrng(xd.r,1,n);
//	cout<<xd.qrylef()<<" "<<xd.qryrig()<<
	if(xd.qrylef()==xd.qryrig())	ret--;
	ret=max(ret,1);
	return ret;
}
int countsegment(int lef,int rig)
{
	lef=idx(lef),rig=idx(rig);
	if(rev)	swap(lef,rig);
	cout<<lef<<"="<<rig<<" "<<mov<<" "<<rev<<endl;
	if(lef<=rig)
	{
		
	//	if(lef==1&&rig==n)	return count();
	//	else	
		return xd.qryrng(xd.r,lef,rig);
	}
	else
	{
	//	cout<<"=="<<lef<<" "<<rig<<endl;
	//	if(lef==rig+1)	return count();
	//	else
	//	{
			int ret=xd.qryrng(xd.r,lef,n)+xd.qryrng(xd.r,1,rig);
			//cout<<xd.qryrig()<<"xxx"<<xd.qrylef()<<" "<<ret<<endl;
			if(xd.qryrig()==xd.qrylef())	ret--;
			return ret;
	//	}
	}
}
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)	scanf("%d",&col[i]);
	xd.r=xd.build(1,n);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		char cmd[10];	scanf("%s",cmd);	int a,b,c;
		if(cmd[0]=='R')	scanf("%d",&c),rotate(c);
		if(cmd[0]=='F')	flip();
		if(cmd[0]=='S')	scanf("%d%d",&a,&b),swp(a,b);
		if(cmd[0]=='P')	scanf("%d%d%d",&a,&b,&c),paint(a,b,c);
		if(cmd[0]=='C')
		{
			if(cmd[1]=='S')	scanf("%d%d",&a,&b),printf("%d\n",countsegment(a,b));
			else	printf("%d\n",count());
		}		
	}
}
