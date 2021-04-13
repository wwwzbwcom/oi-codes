#include<iostream>
#include<map>
using namespace std;
struct Node
{
	int ls,rs;
	int val;
	int ene,sti;
	int mxa,cnt;
}n[1000000];
int nn;
struct Splay
{
	int r;
	int getene()
	{
		return max(n[r].ene,n[r].mxa);
	}
	int getsti()
	{
		return max(n[r].sti,n[r].cnt);
	}
	void push(int u)
	{
		if(n[u].ls!=0)
		{
			n[n[u].ls].ene=max(n[u].ene,n[u].mxa);
			n[n[u].ls].sti=max(n[u].sti,n[u].cnt);
		}
		if(n[u].rs!=0)
		{
			n[n[u].rs].ene=max(n[u].ene,n[u].mxa);
			n[n[u].rs].sti=max(n[u].sti,n[u].cnt);
		}
	}
	void pull(int u)
	{	
		n[u].mxa=max(max(n[n[u].ls].mxa,n[n[u].rs].mxa),n[u].val);
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
	void insert(int &u,int val)
	{
		if(u==0)
		{
			u=++nn;	n[u].ls=n[u].rs=0;	n[u].cnt=1;	n[u].mxa=n[u].val=val;
		}
		else
		{
			push(u);
			if(val<n[u].val)	insert(n[u].ls,val),rrotate(u);
			else	insert(n[u].rs,val),lrotate(u);
		}
	}
	void findkth(int &u,int k)
	{
		if(k==n[n[u].ls].cnt+1)	return;
		else
		{
			push(u);
			if(k<n[n[u].ls].cnt+1)	findkth(n[u].ls,k),rrotate(u);
			else	findkth(n[u].rs,k-n[n[u].ls].cnt-1),lrotate(u);
		}
	}
	void findval(int &u,int val)
	{
		if(val==n[u].val)	return;
		else
		{
			push(u);
			if(val<n[u].val)	findval(n[u].ls,val),rrotate(u);
			else	findval(n[u].rs,val),lrotate(u);
		}
	}
	void goright(int &u)
	{
		if(n[u].rs==0)	return;
		else	push(u),goright(n[u].rs),lrotate(u);
	}
	void eraseval(int &u,int val)
	{
		findval(r,val);
		int k=n[n[r].ls].cnt+1;
		findkth(r,k);
		if(n[r].ls==0)	r=n[r].rs;
		else
		{
			goright(n[r].ls);
			n[n[r].ls].rs=n[r].rs;
			r=n[r].ls;
			pull(r);
		}
	}
}sp[1000000];
map <int,map<int,int> > boo;
int ni,t;
int w[100000],x[100000],y[100000];
int ene[100000],sti[100000];
int bc;
int idx(int x,int y)
{
	if(boo[x][y]==0)
	{
		bc++;
		boo[x][y]=bc;
		return bc;
	}
	else	return boo[x][y];
}
int main()
{
	cin>>ni;
	for(int i=1;i<=ni;i++)
	{
		cin>>w[i]>>x[i]>>y[i];
		int p=idx(x[i],y[i]);
		sp[p].insert(sp[p].r,w[i]);
	}
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int v,xn,yn;	cin>>v>>xn>>yn;
		int op=idx(x[v],y[v]);
		sp[op].eraseval(sp[op].r,w[v]);
		ene[v]=max(ene[v],sp[op].getene());
		sti[v]=max(sti[v],sp[op].getsti());
		int np=idx(xn,yn);
		sp[np].insert(sp[np].r,w[v]);
		x[v]=xn;	y[v]=yn;
	}
	
	for(int i=1;i<=ni;i++)
	{
		int op=idx(x[i],y[i]);
		sp[op].eraseval(sp[op].r,w[i]);
		ene[i]=max(ene[i],sp[op].getene());
		sti[i]=max(sti[i],sp[op].getsti());
		sp[op].insert(sp[op].r,w[i]);
	}
	for(int i=1;i<=ni;i++)	cout<<ene[i]<<" "<<sti[i]<<endl;
}
