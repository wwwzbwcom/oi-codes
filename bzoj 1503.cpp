#include<cstdio> 
#include<algorithm>
using namespace std;
const int maxn=100100;
int n,mni;
class Splay
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int cnt,val;
		}n[maxn];
		int nn;
		void pull(int u)
		{
			n[u].cnt=n[n[u].ls].cnt+n[n[u].rs].cnt+1;
		}
		void lrotate(int &u)
		{
			int rs=n[u].rs;	n[u].rs=n[rs].ls;	n[rs].ls=u;	pull(u);	pull(rs);	u=rs;
		}
		void rrotate(int &u)
		{
			int ls=n[u].ls;	n[u].ls=n[ls].rs;	n[ls].rs=u;	pull(u);	pull(ls);	u=ls;
		}
	public:
		int r,del;
		int size()
		{
			return n[r].cnt;
		}
		int root()
		{
			return n[r].val;
		}
		void insert(int &u,int val)
		{
			if(u==0)	u=++nn,n[u].cnt=1,n[u].val=val;
			else
			{
				if(val>=n[u].val)	insert(n[u].ls,val),rrotate(u);
				else	insert(n[u].rs,val),lrotate(u);
			}
		}
		void qrykth(int &u,int k)
		{
			if(n[n[u].ls].cnt+1==k)	return;
			else
			{
				if(n[n[u].ls].cnt+1>k)	qrykth(n[u].ls,k),rrotate(u);
				else	qrykth(n[u].rs,k-(n[n[u].ls].cnt+1)),lrotate(u);
			}
		}
		void eralas(int &u)
		{
			if(n[n[u].rs].rs!=0)	eralas(n[u].rs),lrotate(u);
			else	n[u].rs=0;
		}
		void alladd(int u,int val)
		{
			n[u].val+=val;
			if(n[u].ls!=0)	alladd(n[u].ls,val);
			if(n[u].rs!=0)	alladd(n[u].rs,val);
		}
		void check()
		{
			if(r==0)	return;
			int tot=n[r].cnt;
			while(1)
			{
				qrykth(r,tot);
				int val=n[r].val;
				if(val>=mni)	break;
				if(n[r].rs==0)	r=n[r].ls;	else	eralas(r);
				tot--;
				del++;
				if(tot==0)	break;
				
			}
		}
}sp;
int main()
{
	scanf("%d%d",&n,&mni);
	for(int i=1;i<=n;i++)
	{
		char cmd[10];	int k;
		scanf("%s%d",cmd,&k);
		if(cmd[0]=='I')	sp.insert(sp.r,k);
		if(cmd[0]=='A')	sp.alladd(sp.r,k);
		if(cmd[0]=='S')	sp.alladd(sp.r,-k);
		if(cmd[0]=='F')
		{
			if(k<=sp.size())
			{
				sp.qrykth(sp.r,k);
				printf("%d\n",sp.root());
			}
			else	printf("%d\n",-1);
		}
		sp.check();
	}
	printf("%d",sp.del);
}
