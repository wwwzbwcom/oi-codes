#include<iostream>
using namespace std;
const int maxn=10010;
int sto[5][maxn];
class XDS
{
	private:
		class Node
		{
			public:
				int ls,rs;
				int le,re;
				int tsum,lsum,rsum,msum;
		}n[maxn*3];
		int nn;
		void pull(int u)
		{
			int ls=n[u].ls,rs=n[u].rs;
			if(ls==0)
			{
				n[u].tsum=n[ls].tsum+n[rs].tsum;
				n[u].lsum=max(n[ls].lsum,n[ls].tsum+n[rs].lsum);
				n[u].rsum=max(n[rs].rsum,n[rs].tsum+n[ls].rsum);
				n[u].msum=max(max(n[ls].msum,n[rs].msum),n[ls].rsum+n[rs].lsum);
			}
		}
	public:
		int idx,r;
		void init()
		{
			nn=r=idx=0;
		}
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			n[u].tsum=n[u].lsum=n[u].msum=n[u].rsum=0;
			if(le==re)
			{
				for(int i=1;i<=4;i++)	if((idx&(1<<(i-1)))==(1<<i-1))
				{
					n[u].tsum+=sto[i][le];
					n[u].lsum+=sto[i][le];
					n[u].msum+=sto[i][le];
					n[u].rsum+=sto[i][le];
				}
				n[u].ls=n[u].rs=0;
			}
			else
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re); 
			}
			return u;
		}
		int change(int u,int pos,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)	n[u].tsum=n[u].lsum=n[u].msum=n[u].rsum=val;
			else
			{
				if(pos<=mid)	change(n[u].ls,pos,val);
				else	change(n[u].rs,pos,val);
				pull(u); 
			}
		}
		int query(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==lc&&re==rc)	return n[u].msum;
			else
			{
				if(rc<=mid)	return query(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	return query(n[u].rs,lc,rc);
					else	return max(query(n[u].ls,lc,mid),query(n[u].rs,mid+1,rc));
				}
			}
		}
}sid[5],mid[5];
int query(int y1,int x1,int y2,int x2)
{
	int sum=0;
	for(int i=y1;i<=y2;i++)	if(i==1||i==3||i==4)
		for(int j=x1;j<=x2;j++)
			sum+=sto[i][j];
	cout<<sum<<endl;
	if(y2-y1+1<3)	return 0;
	int ans=0; 
	if(y2-y1+1>=4)
	{
		for(int i=0;i<5;i++)	ans=max(ans,sid[i].query(sid[i].r,x1,x2)+mid[i].query(mid[i].r,x1,x2));
		return ans;
	}
	else
	{
		if(y1==2)	return sid[3].query(sid[3].r,x1,x2)+mid[3].query(mid[3].r,x1,x2);
		if(y1==1)	return sid[4].query(sid[4].r,x1,x2)+mid[4].query(mid[4].r,x1,x2);
	}
}
void change(int y1,int x1,int val)
{
	for(int i=0;i<5;i++)
	{
		if((sid[i].idx&(1<<(y1-1)))==(1<<(y1-1)))	sid[i].change(sid[i].r,x1,val);
		if((mid[i].idx&(1<<(y1-1)))==(1<<(y1-1)))	mid[i].change(mid[i].r,x1,val);
	}
}
int gn,n,m;
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n;
		for(int i=0;i<5;i++)	sid[i].init(),mid[i].init();
		sid[0].idx=9;	mid[0].idx=6;	//1001 0110
		sid[1].idx=11;	mid[1].idx=4;	//1101 0010
		sid[2].idx=13;	mid[2].idx=2;	//1011 0100
		sid[3].idx=10;	mid[3].idx=4;	//0101 0010
		sid[4].idx=5;	mid[4].idx=2;	//1010 0100
		for(int i=1;i<=4;i++)	for(int j=1;j<=n;j++)	cin>>sto[i][j];
		for(int i=0;i<5;i++)	sid[i].r=sid[i].build(1,n),mid[i].r=mid[i].build(1,n);
		//cout<<"==="<<endl;
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			int cmd,x1,y1,x2,y2,val;
			cin>>cmd;
			if(cmd==1)
			{
				cin>>y1>>x1>>y2>>x2;
				cout<<query(y1,x1,y2,x2)<<endl;
			}
			else
			{
				cin>>y1>>x1>>val;
				change(y1,x1,val);
			}
		}
	}
}
