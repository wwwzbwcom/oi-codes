#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1000100;
int n,m;
int itr[maxn];
int idx[maxn];
int tim=0,ans=0;
void bd()
{
	queue <int> que;
	while(1)	que.push(1); 
}
struct XDS
{
	XDS()
	{
		n[0].num=0;
		n[0].sum=0;
		n[0].mni=1e9;
	}
	struct Node
	{
		int ls,rs;
		int le,re;
		int num,sum,mni,tim;
	}n[maxn*2];
	int nn;
	void upload(int u)
	{
		if(u==0)	bd(); 
		n[u].sum=n[n[u].ls].sum+n[n[u].rs].sum;
		if(n[n[u].ls].mni<n[n[u].rs].mni)	n[u].mni=n[n[u].ls].mni,n[u].tim=n[n[u].ls].tim;
		else	n[u].mni=n[n[u].rs].mni,n[u].tim=n[n[u].rs].tim;
	}
	int build(int le,int re)
	{
		int u=++nn;
		n[u].le=le;	n[u].re=re;
		n[u].num=0;	n[u].sum=0;	n[u].mni=1e9;
		if(le==re)	n[u].ls=n[u].rs=0;
		else
		{
			int mid=(le+re)/2;
			n[u].ls=build(le,mid);
			n[u].rs=build(mid+1,re);
		}
		return u;
	}
	void change(int u,int pos,int num,int tim)
	{
		if(u==0)	bd(); 
		int le=n[u].le,re=n[u].re;
		int ls=n[u].ls,rs=n[u].rs;
		int mid=(le+re)/2;
		
		if(le==re)
		{
			itr[n[u].num]=0;	itr[num]=1;
			idx[num]=le;
			n[u].num=num;
			n[u].sum=1;
			n[u].mni=1;
			n[u].tim=tim;
			return;
		}
		if(pos<=mid)	change(ls,pos,num,tim);
		else	change(rs,pos,num,tim);
		
		upload(u);
	//	cout<<"="<<u<<" "<<n[n[u].ls].mni<<" "<<n[n[u].rs].mni<<" "<<n[u].mni<<endl;
	}
	void add(int u,int pos)
	{
		if(u==0)	bd();
		int le=n[u].le,re=n[u].re;
		int ls=n[u].ls,rs=n[u].rs;
		int mid=(le+re)/2;
		
		if(le==re)
		{
			n[u].mni++;
			return;
		}
		
		if(pos<=mid)	add(ls,pos);
		else	add(rs,pos);
		
		upload(u);
	}
	int findempty(int u)
	{
		if(u==0)	bd();
		int le=n[u].le,re=n[u].re;
		int ls=n[u].ls,rs=n[u].rs;
		int mid=(le+re)/2;
		
		if(le==re)
		{
			if(n[u].sum==0)	return le;
			else	return -1;
		}
		if(n[ls].sum<(mid-le+1))	return findempty(ls);
		else
		{
			if(n[rs].sum<(re-(mid+1)+1))	return findempty(rs);
			else	return -1;
		}
	}
	int findmin(int u)
	{
		if(u==0)	bd();
		int le=n[u].le,re=n[u].re;
		int ls=n[u].ls,rs=n[u].rs;
		int mid=(le+re)/2;
		
		if(le==re)	return le;
		
		if(n[ls].mni==n[rs].mni)
		{
			if(n[ls].tim<n[rs].tim)	return findmin(ls);
			else	return findmin(rs);
		}
		else
		{ 
			if(n[ls].mni<n[rs].mni)	return findmin(ls);
			else	return findmin(rs);
		}
	}
	void debug()
	{
		for(int u=1;u<=nn;u++);
	//	cout<<u<<" "<<n[u].ls<<"="<<n[u].rs<<" "<<n[u].le<<"="<<n[u].re<<" "<<n[u].num<<" "<<n[u].sum<<" "<<n[u].mni<<endl;
	}
}xds;
int main()
{
	scanf("%d%d",&n,&m);
	xds.build(1,n);
	for(int i=1;i<=m;i++)
	{
		int num,t;	scanf("%d",&num);
		tim++;
	//	cout<<"====="<<xds.n[1].sum<<endl;
		if(itr[num]==1)	ans++,xds.add(1,idx[num]);//cout<<1<<"=="<<endl;
		else
		{
			int t=xds.findempty(1);
			if(t!=-1)	xds.change(1,t,num,tim);//cout<<2<<"=="<<t<<endl;
			else
			{
				t=xds.findmin(1);
			//	cout<<3<<"=="<<t<<"=="<<num<<endl;
				xds.change(1,t,num,tim);
			}
		}
	//	xds.debug();
	}
	printf("%d",ans);
}
