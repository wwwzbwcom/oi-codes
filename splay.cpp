#include<cstdio>
using namespace std;
int n,m;
struct Splay
{
	struct Node
	{
		int lc,rc;
		int y,r;
		int fy,ly,ry;
		int fr,lr,rr;
	}n[50100];
	int nn;
	int root;
	void update(int u)
	{
	//	cout<<n[u].y<<endl;
		int lc=n[u].lc,rc=n[u].rc;
		if(lc==0&&rc==0)	n[u].fy=1,n[u].ly=n[u].ry=n[u].y,n[u].fr=1,n[u].lr=n[u].rr=n[u].r;
		else
		{
			if(lc!=0&&rc!=0)
			{
				if(n[lc].fy==1&&n[rc].fy==1&&n[lc].ry+1==n[u].y&&n[u].y+1==n[u].ly)	n[u].fy=1;	else	n[u].fy=0;
				if(n[lc].fr==1&&n[rc].fr==1&&n[lc].lr<n[u].r&&n[u].r<n[rc].rr)	n[u].fr=1;	else	n[u].fr=0;
				n[u].ly=n[lc].ly;	n[u].ry=n[rc].ry;	n[u].lr=n[lc].lr;	n[u].rr=n[rc].rr;
			}
			else
			{
				if(lc==0)
				{
					if(n[rc].fy==1&&n[u].y+1==n[rc].ly)	n[u].fy=1;	else	n[u].fy=0;
					if(n[rc].fr==1&&n[u].r<n[rc].lr)	n[u].fr=1;	else	n[u].fr=0;
					n[u].ly=n[u].y;	n[u].ry=n[rc].ry;	n[u].lr=n[u].r;	n[u].rr=n[rc].rr;
				}
				else
				{
					if(n[lc].fy==1&&n[lc].ry+1==n[u].y)	n[u].fy=1;	else	n[u].fy=0;
					if(n[lc].fr==1&&n[lc].rr<n[u].r)	n[u].fr=1;	else	n[u].fr=0;
					n[u].ly=n[lc].ly;	n[u].ry=n[u].y;	n[u].lr=n[lc].lr;	n[u].rr=n[u].r;
				} 
			}
		}
	}
	void lrotate(int &u)
	{
		int rc=n[u].rc;	n[u].rc=n[rc].lc;	n[rc].lc=u;	update(u);	update(rc);	u=rc;
	}
	void rrotate(int &u)
	{
		int lc=n[u].lc;	n[u].lc=n[lc].rc;	n[lc].rc=u;	update(u);	update(lc);	u=lc;
	}
	void insert(int &u,int y,int r)
	{
		if(u==0)
		{
			u=++nn;
			n[u].lc=n[u].rc=0;
			n[u].y=y;	n[u].r=r;
			n[u].fy=1;	n[u].ly=y;	n[u].ry=y;
			n[u].fr=1;	n[u].lr=r;	n[u].ry=r;
		}
		else
		{
			if(y<=n[u].y)	insert(n[u].lc,y,r),rrotate(u);
			else	insert(n[u].rc,y,r),lrotate(u);
		}
	}
	bool findlas(int &u,int val)
	{
		if(u==0)	return 0;
		if(val<=n[u].y)
		{
			if(findlas(n[u].lc,val))
			{
				rrotate(u);
				return 1;
			}
			else	return 0;
		}
		else
		{
			if(findlas(n[u].rc,val))
			{
				lrotate(u);
				return 1;
			}
			else	return 1;
		}
	}
	bool findnxt(int &u,int val)
	{
		if(u==0)	return 0;
		if(val<n[u].y)
		{
			if(findnxt(n[u].lc,val))
			{
				rrotate(u);
				return 1;
			}
			else	return 1;
		}
		else
		{
			if(findnxt(n[u].rc,val))
			{
				lrotate(u);
				return 1;
			}
			else	return 0;
		}
	}
	int find(int &u,int val)
	{
		if(n[u].y==val)	return n[u].r;
		else
		{
			int t;
			if(val<n[u].y)
			{
				if(n[u].lc==0)	return -1;
				else	t=find(n[u].lc,val),rrotate(u);
			}
			else
			{
				if(n[u].rc==0)	return -1;
				else	t=find(n[u].rc,val),lrotate(u);
			}
			return t;
		}
	}
	void work(int s,int e)
	{
		s++;
		findlas(root,s);
		findnxt(n[root].rc,e);
		int u=n[n[root].rc].lc;
	//	cout<<n[u].y<<"="<<n[u].r<<" "<<n[u].ly<<" "<<n[u].ry<<endl;
	//	cout<<n[n[u].lc].y<<"="<<n[n[u].lc].r<<" "<<n[n[u].lc].ly<<" "<<n[n[u].rc].ry<<endl;
	//	cout<<n[n[u].rc].y<<"="<<n[n[u].rc].r<<" "<<n[n[u].rc].ly<<" "<<n[n[u].rc].ry<<endl;
		int fr=n[u].fr,fy=n[u].fy,ly=n[u].ly,ry=n[u].ry;
		if(u==0)	printf("maybe");
		else
		{
			if(fr==0)	printf("false");
			else
			{
				if(find(root,s-1)==-1)	printf("maybe");
				else
				{
					if(find(root,s-1)<find(root,e))	printf("false");
					else
					{
					//	cout<<ly<<" "<<ry<<endl;
						if(fy&&ly==s&&ry==e)	printf("true");
						else	printf("maybe");
					}
				}
			}	
		}
		printf("\n");
	}
}sp;
int main()
{
	sp.insert(sp.root,-1e9-1,0);
	sp.insert(sp.root,1e9+1,0);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int y,r;	scanf("%d%d",&y,&r);
		sp.insert(sp.root,y,r);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int s,e;	scanf("%d%d",&s,&e);
		sp.work(s,e);
	}
}
