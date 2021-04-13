#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
void bd()
{
	puts("=================");
	queue <int> q;
	while(1)	q.push(1);
}
struct Splay
{
	struct Node
	{
		char c;
		int ls,rs;
		int cnt,rev;
	}n[4000000];
	int r,nn;
	void push(int u)
	{
		if(u!=0)
		if(n[u].rev==1)
		{
			n[n[u].ls].rev^=1;
			n[n[u].rs].rev^=1;
			n[u].rev=0;
			swap(n[u].ls,n[u].rs);
		}
	}
	void pull(int u)
	{
		if(u!=0)
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
	void insert(int &u,char c)
	{
		if(u==0)
		{
			u=++nn;
			n[u].c=c;
			n[u].ls=n[u].rs=0;
			n[u].cnt=1;
			n[u].rev=0;
		}
		else	insert(n[u].rs,c),lrotate(u);
	}
	void findkth(int &u,int aim)
	{
	//	if(u==0)	bd();
		push(u);
		if(n[n[u].ls].cnt+1==aim)		return;
		else
		{
			if(n[n[u].ls].cnt>=aim)	findkth(n[u].ls,aim),rrotate(u);
			else	findkth(n[u].rs,aim-n[n[u].ls].cnt-1),lrotate(u);
		}
	}
	void rangeopt(int a,int b,int mod)
	{
		findkth(r,a);
		findkth(n[r].rs,b-n[n[r].ls].cnt-1);
		int u=n[r].rs;
		push(r);	push(u);	push(n[u].ls);
		
		if(mod==1)
		{
			int len;	char c;	scanf("%d",&len);	getchar();
			for(int i=0;i<len;i++)	c=getchar(),insert(n[u].ls,c);
		}
		if(mod==2)	n[u].ls=0;
		if(mod==3)	n[n[u].ls].rev^=1;
		pull(n[u].ls);	pull(u);	pull(r);
	}
}sp;
int n,p;
int main()
{
	scanf("%d",&n);
	sp.insert(sp.r,'#');
	sp.insert(sp.r,'#');
	p=1;
	for(int i=1;i<=n;i++)
	{
		char cmd[20];	int a;	scanf("%s",cmd);
		if(cmd[0]=='M')	scanf("%d",&a),p=a+1;
		if(cmd[0]=='I')	sp.rangeopt(p,p+1,1);
		if(cmd[0]=='D')	scanf("%d",&a),sp.rangeopt(p,p+1+a,2);
		if(cmd[0]=='R')	scanf("%d",&a),sp.rangeopt(p,p+1+a,3);
		if(cmd[0]=='G')	sp.findkth(sp.r,p+1),putchar(sp.n[sp.r].c),putchar('\n');
		if(cmd[0]=='P')	p--;
		if(cmd[0]=='N')	p++;
	}
}
