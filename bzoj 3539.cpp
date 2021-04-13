#include<iostream>
#include<map>
using namespace std;
const int maxn=;
struct Splay
{
	struct Node
	{
		int ls,rs,fa;
		int val,cnt;
	}n[maxn];
	int nn,r;
	void pull(int u)
	{
		n[u].cnt=n[n[u].ls].cnt+n[n[u].rs].cnt+1; 
	}
	void lrotate(int &u)
	{
		int rs=n[u].rs;	n[u].rs=n[rs].ls;	n[n[u].rs].fa=u;	n[rs].ls=u;	n[rs].fa=n[u].fa;	n[u].fa=rs;	pull(u);	pull(rs);	u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;	n[u].ls=n[ls].rs;	n[n[u].ls].fa=u;	n[ls].rs=u;	n[ls].fa=n[u].fa;	n[u].fa=ls;	pull(u);	pull(ls);	u=ls;
	}
	void rinsert(int &u,int key)
	{
		if(n[u].rs==0)
		{
			u=++nn;
			n[u].key=key;
			n[u].cnt=1;
		}
		else
		{
			if(n[n[u].rs].rs!=0)	lrotate(u);
			insert(n[u].rs);	lrotate(u);
		}
	}
	void linsert(int &u)
	{
		if(n[u].ls==0)
		{
			u=++nn;
			n[u].cnt=1;
		}
		else
		{
			if(n[n[u].ls].ls!=0)	rrotate(u);
			insert(n[u].ls);	rrotate(u);
		}
	}
	void rgo(int &u)
	{
		if(n[u].rs==0)	return;
		else
		{
			if(n[n[u].rs].rs!=0)	lrotate(u);
			rgo(n[u].rs);	lrotate(u);
		}
	}
	void findkth(int &u,int kth)
	{
		if(kth==n[n[u].ls].cnt+1)	return;
		else
		{
			if(kth<n[n[u].ls].cnt+1)
			{
				if(kth<n[n[n[u].ls].ls].cnt+1)	rrotate(u);
				findkth(n[u].ls,kth),rrotate(u);
			}
			else
			{
				if(kth>n[n[n[u].rs].ls].cnt+1)	lrotate(u);
				findkth(n[u].ls,kth-(n[n[u].ls].cnt+1)),lrotate(u);
			}
		}
	}
	void getkth(int u)
	{
		int ans=n[n[u].ls].cnt+1;
		while(u!=r)
		{
			int tmp=n[u].fa;
			if(n[tmp].rs==u)	ans+=n[n[tmp].ls].cnt+1;
			u=tmp;
		}
		return ans;
	}
	void erase(int kth)
	{
		findkth(r,kth);
		
		if(n[r].ls==0)	r=n[r].rs;
		else
		{
			rgo(n[r].ls);
			n[n[r].ls].rs=n[r].rs;
			r=n[r].ls;
		}
	}
}sp;
map <int,int> boo;
int main()
{
	int n,m;	cin>>n>>m;
	int a=0;
	for(int i=1;i<=n;i++)	sp.rinsert(sp.r),boo[i]=sp.r;
	for(int i=1;i<=m;i++)
	{
		int cmd,x,y;
		scanf("%d",&cmd);
		if(cmd==1)	scanf("%d%d",&x,&y);
		else
		{
			scanf("%d",&x);
			if(cmd==2)	sp.erase(sp.getkth(boo[x])),sp.linsert(sp.r),boo[x]=sp.r;
			if(cmd==3)	sp.erase(sp.getkth(boo[x])),sp.rinsert(sp.r),boo[x]=sp.r;
			if(cmd==4)	sp.findkth(sp.r,x)
		}
		
	}
}
