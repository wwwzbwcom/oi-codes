#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=10000;
int num;
struct NODE
{
	int ls,rs;
	int le,re,mi;
	int col,opt;
}n[maxn];
int nn,r;
struct RANGE
{
	RANGE()
	{
	}
	RANGE(int lei,int rei,int ui)
	{
		le=lei;	re=rei;	u=ui;
	}
	int le,re,u;
	bool operator <(const RANGE &in)const
	{
		return le<in.le;
	}
}rng[maxn];
int rn;
int dfs1(int le,int re)
{
	int u=++nn;
	n[u].le=le;	n[u].re=re;
	if(le==re)	cin>>n[u].col;
	else
	{
		cin>>n[u].col>>n[u].mi;
		
		n[u].ls=dfs1(le,n[u].mi);
		n[u].rs=dfs1(n[u].mi+1,re);
	}
	return u;
}
int flag=0;
void dfs2(int u,int opt,int col)
{
	n[u].opt=opt;
	cout<<n[u].le<<"="<<n[u].re<<"="<<n[u].col<<endl;
	if(n[u].col==0)	col=0;
	else
	{
		if(col==0)	flag=1;
		
		if(n[n[u].ls].col==0&&n[n[u].rs].col==0||n[u].le==n[u].re)	rng[rn++]=RANGE(n[u].le,n[u].re,u);
	}
	if(n[u].le!=n[u].re)
	{
		dfs2(n[u].ls,n[u].rs,col);
		dfs2(n[u].rs,n[u].ls,col);
	}
}
int ans=0;
int main()
{
	cin>>num;
	r=dfs1(1,num);
	dfs2(r,-1,1);
	if(flag==1)	cout<<"OwO"<<endl;
	else
	{
		sort(rng,rng+rn);
		ans=1;
		for(int i=1;i<rn;i++)
		{
			if(n[rng[i-1].u].opt!=rng[i].u&&rng[i-1].re+1==rng[i].le)	continue;
			else	ans++;
		}
		cout<<ans<<endl; 
	}
}
