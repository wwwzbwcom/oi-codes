//#pragma comment(linker, "/STACK:10240000000,10240000000") 
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
int num,m;
struct Splay
{
	struct Node
	{
		int ls,rs;
		int num,sum;
		int mar;
	}n[100100];
	int nn,root;
	void download(int u)
	{
		int ls=n[u].ls,rs=n[u].rs;
		if(n[u].mar==1)
		{
			n[u].mar=0;
			n[ls].mar^=1;
			n[rs].mar^=1;
			swap(n[u].ls,n[u].rs);
		}
	}
	void upload(int u)
	{
		if(u==0)	return;
		int ls=n[u].ls,rs=n[u].rs;
		n[u].sum=n[ls].sum+n[rs].sum+1;
	}
	void lrotate(int &u)
	{
		int rs=n[u].rs;
		download(u);	download(rs);
		n[u].rs=n[rs].ls;	n[rs].ls=u;
		upload(u);	upload(rs);
		u=rs;
	}
	void rrotate(int &u)
	{
		int ls=n[u].ls;
		download(u);	download(ls);
		n[u].ls=n[ls].rs;	n[ls].rs=u;
		upload(u);	upload(ls);
		u=ls;
	}
	void insert(int &u,int num)
	{
		if(u==0)
		{
			u=++nn;
			n[u].num=num;
			n[u].sum=1;
		}
		else
		{
			insert(n[u].rs,num);
			lrotate(u);
		}
	}
	int find(int &u,int pos)
	{
		if(n[n[u].ls].sum==pos-1)	return n[u].num;
		else
		{
			int t;
			if(pos<=n[n[u].ls].sum)
			{
				if(pos<=n[n[n[u].ls].ls].sum)	rrotate(u);
				t=find(n[u].ls,pos);
				rrotate(u);
			}
			else	if(pos>n[n[u].ls].sum+1)
			{
				if((pos-n[n[u].ls].sum-1)>n[n[n[u].rs].ls].sum+1)	lrotate(u);
				t=find(n[u].rs,pos-n[n[u].ls].sum-1);
				lrotate(u);
			}
			return t;
		}
	}
	void reverse(int s,int e)
	{
	//	debug();
		find(root,(s-1)+1);
	//	debug();
		find(n[root].rs,(e+1)+1-n[n[root].ls].sum-1);
	//	cout<<n[root].num<<" "<<n[n[root].rs].num<<" "<<n[n[root].rs].sum<<endl;
		n[n[n[root].rs].ls].mar^=1;
	}
/*
	void debug()
	{
		cout<<root<<endl;
		for(int i=1;i<=nn;i++)	cout<<i<<" "<<n[i].num<<" "<<n[i].ls<<"="<<n[i].rs<<endl; 
		cout<<"==============="<<endl;
	}
*/
	void output(int u,int d)
	{
		if(u==0)	return;
		if(n[u].mar)	download(u);
		output(n[u].ls,d+1);
		if(n[u].num!=0&&n[u].num!=num+1)	printf("%d ",n[u].num);
		output(n[u].rs,d+1);
	}
}sp;
int main()
{
/*
	int size = 80 << 20; // 256MB
	char *p = (char*)malloc(size) + size;  
	__asm__("movl %0, %%esp\n" :: "r"(p));
*/
	scanf("%d%d",&num,&m);
	for(int i=0;i<=num+1;i++)
	{
		sp.insert(sp.root,i);
	}
	for(int i=1;i<=m;i++)
	{
		int s,e; scanf("%d%d",&s,&e);
		sp.reverse(s,e);
	}
	sp.output(sp.root,0);
}
