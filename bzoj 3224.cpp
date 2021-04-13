#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int maxn=100100;
int cnt=0;
struct Treap
{
	struct Node
	{
		int ls,rs;
		int val,cnt,sum;
		int fix;
	}n[maxn];
	int nn;
	int root;
	void update(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		n[u].sum=n[ls].sum+n[rs].sum+n[u].cnt;
	}
	void lrotate(int &u)
	{
		int rs=n[u].rs;	n[u].rs=n[rs].ls;	n[rs].ls=u;	update(u);	update(rs);	u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;	n[u].ls=n[ls].rs;	n[ls].rs=u;	update(u);	update(ls);	u=ls;
	}
	void insert(int &u,int val)
	{
		if(u==0)
		{
			u=++nn;
			n[u].ls=n[u].rs=0;
			n[u].val=val;	n[u].cnt=1;	n[u].sum=1;
			n[u].fix=rand();
		}
		else
		{
			if(n[u].val==val)	n[u].cnt++,update(u);
			else
			{
				if(n[u].val>val)
				{
					insert(n[u].ls,val);
					if(n[n[u].ls].fix>n[u].fix)	rrotate(u);
					update(u);
				}
				else
				{
					insert(n[u].rs,val);
					if(n[n[u].rs].fix>n[u].fix)	lrotate(u);
					update(u);
				}
			}
		}
	}
	void delet(int u,int val)
	{
		if(u==0)	return;
		if(n[u].val==val)	n[u].cnt--;
		else
		{
			if(n[u].val>val)	delet(n[u].ls,val);
			else	delet(n[u].rs,val);
		}
		update(u);
	}
	int query(int u,int val)
	{
	//	printf("%d %d\n",u,n[u].val);
		if(n[u].val==val)	return n[n[u].ls].sum+1;
		else
		{
			if(n[u].val>val)	return query(n[u].ls,val);
			else	return query(n[u].rs,val)+n[n[u].ls].sum+n[u].cnt;
		}
	}
	int kth(int u,int k)
	{
		int ls=n[u].ls,rs=n[u].rs;
	//	if(u!=0)	printf("%d=%d %d=%d %d\n",u,n[u].sum,n[ls].sum,n[rs].sum,k);
		if(n[ls].sum<=k-1&&n[ls].sum+n[u].cnt>=k)	return n[u].val;
		else
		{
			if(n[ls].sum>=k)	return kth(ls,k);
			else	return kth(rs,k-n[ls].sum-n[u].cnt);
		}
	}
	int findlas(int u,int val,int cur)
	{
		if(u==0)	return cur;
		if(n[u].val<val)
		{
			if(n[u].cnt>0)	return findlas(n[u].rs,val,n[u].val);
			else	return max(findlas(n[u].ls,val,cur),findlas(n[u].rs,val,cur));
		}
		else	return findlas(n[u].ls,val,cur);
	}
	int findnxt(int u,int val,int cur)
	{
		if(u==0)	return cur;
	 	if(n[u].val<=val)	return findnxt(n[u].rs,val,cur);
		else
		{	
			if(n[u].cnt>0)	return findnxt(n[u].ls,val,n[u].val);
			else	return min(findnxt(n[u].rs,val,cur),findnxt(n[u].ls,val,cur));
		}
	}
}tre;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int cmd,val;	scanf("%d%d",&cmd,&val);
		
		if(cmd==1)	tre.insert(tre.root,val);
		if(cmd==2)	tre.delet(tre.root,val);
		if(cmd==3)	printf("%d\n",tre.query(tre.root,val));
		if(cmd==4)	printf("%d\n",tre.kth(tre.root,val));
		if(cmd==5)	printf("%d\n",tre.findlas(tre.root,val,0));
		if(cmd==6)	printf("%d\n",tre.findnxt(tre.root,val,1e8));
	}
} 
