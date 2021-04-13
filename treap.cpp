#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
const int maxn=1000100;
struct Treap
{
	struct Node
	{
		int ls,rs;
		int val,cnt;
		int fix;
	}n[maxn];
	int nn;
	void lrotate(int &u)
	{
		int rs=n[u].rs;
		n[u].rs=n[rs].ls;	n[rs].ls=u;	u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;
		n[u].ls=n[ls].rs;	n[ls].rs=u;	u=ls;
	}
	void update(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		n[u].cnt=n[ls].cnt+n[rs].cnt+1;
	}
	void insert(int &u,int val)
	{
		if(u==0)
		{
			u=++nn;
			n[u].val=val;	n[u].cnt=1;
			n[u].fix=rand();
			n[u].ls=n[u].rs=0;
		}
		else
		{
			if(val<=n[u].val)
			{
				insert(n[u].ls,val);
				if(n[n[u].ls].fix<n[u].fix)	rrotate(u);
				update(u);
			}
			else
			{
				insert(n[u].rs,val);
				if(n[n[u].rs].fix<n[u].fix)	lrotate(u);
				update(u);
			}
		}
	}
	int kth(int u,int k)
	{
	//	cout<<u<<" "<<k<<endl;
		if(k<=0||k>n[u].cnt)	return -1; 
		int ls=n[u].ls,rs=n[u].rs;
		if(n[ls].cnt==k-1)	return n[u].val;
		else
		{
			if(n[ls].cnt>k-1)	return kth(ls,k);
			else	return kth(rs,k-1-n[ls].cnt);
		}
	}
	void debug()
	{
		for(int i=1;i<=nn;i++)	cout<<i<<" "<<n[i].ls<<" "<<n[i].rs<<" "<<n[i].cnt<<" "<<n[i].val<<endl;
	}
}tre;
int n;
int root;
int main()
{
	cin>>n;
	srand(n);
	root=0;
	for(int i=1;i<=n;i++)
	{
		int cmd,val;	cin>>cmd>>val;
		if(cmd==1)	tre.insert(root,val);
		else	cout<<tre.kth(root,val)<<endl;
	}
//	tre.debug();
}
