#include<cstdio>
#include<algorithm>
using namespace std;
const int oo=10000;
class Splay
{
	private:
		class Node
		{
			public:
				Node()
				{
					ls=rs=0;
					val=set=rev=cnt=lsu=rsu=msu=sum=0;
				}
				Node *ls,*rs;
				int val;
				int set,rev,cnt;
				int lsu,rsu,msu,sum;
		};
		Node *emp;
		void push(Node *u)
		{
			Node *ls=u->ls,*rs=u->rs;
			if(ls!=emp)
			{
				if(u->set!=oo)	ls->set=u->set;
				if(u->rev)		ls->rev^=u->rev;
			}
			if(rs!=emp)
			{
				if(u->set!=oo)	rs->set=u->set;
				if(u->rev)		rs->rev^=u->rev;
			}
			if(u->set!=oo)	u->val=u->set,u->set=oo;
			if(u->rev)	u->rev=0,swap(u->ls,u->rs);
		}
		void pull(Node *u)
		{
			Node *ls=u->ls,*rs=u->rs;
			int lslsu,lsrsu,lsmsu,lssum;
			int rslsu,rsrsu,rsmsu,rssum;
			if(ls->rev==0&&ls->set==oo)	lslsu=ls->lsu,lsrsu=ls->rsu,lsmsu=ls->msu,lssum=ls->sum;
			else
			{
				if(ls->set!=oo)	lslsu=lsrsu=lsmsu=max(ls->set,ls->cnt*ls->set),lssum=ls->cnt*ls->set;
				else	lsrsu=ls->lsu,lslsu=ls->rsu,lsmsu=ls->msu,lssum=ls->sum;
			}
			if(rs->rev==0&&rs->set==oo)	rslsu=rs->lsu,rsrsu=rs->rsu,rsmsu=rs->msu,rssum=rs->sum;
			else
			{
				if(rs->set!=oo)	rslsu=rsrsu=rsmsu=max(rs->set,rs->cnt*rs->set),rssum=rs->cnt*rs->set;
				else	rsrsu=rs->lsu,rslsu=rs->rsu,rsmsu=rs->msu,rssum=rs->sum;
			}
			u->lsu=max(lslsu,lssum+u->val+max(0,rslsu));
			u->rsu=max(rsrsu,rssum+u->val+max(0,lsrsu));
			u->msu=max(max(lsmsu,rsmsu),max(0,lsrsu)+u->val+max(0,rslsu));
			u->sum=lssum+rssum+u->val;
			u->cnt=ls->cnt+rs->cnt+1;
		}
		void lrotate(Node *&u)
		{
			Node *rs=u->rs;	u->rs=rs->ls;	rs->ls=u;	pull(u);	pull(rs);	u=rs;
		}
		void rrotate(Node *&u)
		{
			Node *ls=u->ls;	u->ls=ls->rs;	ls->rs=u;	pull(u);	pull(ls);	u=ls;
		}
		
		void findkth(Node *&u,int k)
		{
			push(u);
			if(u->ls->cnt+1==k)
			{
				pull(u);
				return;
			}
			else
			{
				if(u->ls->cnt+1>k)
				{
					push(u->ls);
					if(u->ls->ls->cnt+1>k)	rrotate(u);
					else	pull(u->ls);
					findkth(u->ls,k),rrotate(u);
				}
				else
				{
					push(u->rs);
					if(u->rs->ls->cnt+1<k-(u->ls->cnt+1))	lrotate(u);
					else	pull(u->rs);
					findkth(u->rs,k-(u->ls->cnt+1)),lrotate(u);
				}
			}
		}
	public:
		Node *r;
		Splay()
		{
			emp=new Node();
			emp->ls=emp->rs=0; 
			emp->val=emp->rev=emp->cnt=0;
			emp->set=oo;
			emp->lsu=emp->rsu=emp->msu=-oo;
			emp->sum=0;
			r=emp;
			insert(r,oo);
			insert(r,oo);
		}
		int size()
		{
			return (r->cnt)-2;
		}
		void insert(Node *&u,int val)
		{
			if(u==emp)
			{
				u=new Node();
				u->ls=u->rs=emp;
				u->val=val;
				u->set=oo;	u->rev=0;
				u->lsu=u->rsu=u->msu=val;
				u->sum=val;
				u->cnt=1;
			}
			else
			{
				push(u);
				if(u->rs!=emp)	lrotate(u);
				insert(u->rs,val);	lrotate(u);
			}
		}
		void erase(Node *u)
		{
			if(u==emp)	return;
			else
			{
				erase(u->ls);
				erase(u->rs);
				delete u;
			}
		}
		void operate(int le,int re,int val,int mod)
		{
			le++;	re++;
			
			findkth(r,le-1);
			push(r);
			findkth(r->rs,(re+1)-(r->ls->cnt+1));
			
			int tmp;
			if(mod==1)	for(int i=1;i<=val;i++)	scanf("%d",&tmp),insert(r->rs->ls,tmp);
			if(mod==2)	erase(r->rs->ls),r->rs->ls=emp;
			if(mod==3)	r->rs->ls->set=val;
			if(mod==4)	r->rs->ls->rev=1;
			if(mod==5)	
			{
				if(r->rs->ls->set==oo)	printf("%d\n",r->rs->ls->sum);
				else	printf("%d\n",r->rs->ls->cnt*r->rs->ls->set);
			}
			if(mod==6)
			{
				if(r->rs->ls->set==oo)	printf("%d\n",r->rs->ls->msu);
				else	printf("%d\n",max(r->rs->ls->set,r->rs->ls->cnt*r->rs->ls->set));
			}
			pull(r->rs);
			pull(r);
		}
}sp;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	sp.operate(1,0,n,1);
	for(int i=1;i<=m;i++)
	{
		char cmd[100];	int pos,tot,val;
		scanf("%s",cmd);
		if(cmd[0]=='I')	scanf("%d%d",&pos,&tot),		sp.operate(pos+1,pos,tot,1);
		if(cmd[0]=='D')	scanf("%d%d",&pos,&tot),		sp.operate(pos,pos+tot-1,0,2);
		if(cmd[2]=='K')	scanf("%d%d%d",&pos,&tot,&val),	sp.operate(pos,pos+tot-1,val,3);
		if(cmd[0]=='R')	scanf("%d%d",&pos,&tot),		sp.operate(pos,pos+tot-1,0,4);
		if(cmd[0]=='G')
		{
			scanf("%d%d",&pos,&tot);
			if(tot==0)	printf("%d\n",0);
			else	sp.operate(pos,pos+tot-1,0,5);
		}
		if(cmd[2]=='X')									sp.operate(1,sp.size(),0,6);
	}
}
