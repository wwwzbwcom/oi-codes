#include<cstdio>
using namespace std;
const int mod=1e8+7;
const int maxn=100001;
int sto[maxn];
struct XDS
{
	struct Node
	{
		Node()
		{
			ls=rs=NULL;
			tcnt=lcnt=rcnt=0;
			sum=0;
		}
		Node *ls,*rs;
		bool tcnt;
		int lcnt,rcnt;
		int sum;
	};
	Node *r;
	Node poo[2*maxn];
	int nn;
	int sto[maxn];
	Node *build(int le,int re,int p)
	{
		Node *u=&poo[nn++];
		if(le==re)	sto[le]=u->lcnt=u->rcnt=u->tcnt=u->sum=(::sto[le]>>p)%2;
		else
		{
			int mid=(le+re)>>1;
			u->ls=build(le,mid,p);
			u->rs=build(mid+1,re,p); 
			pull(le,re,u);
		}
		return u;
	}
	void pull(int le,int re,Node *u)
	{
		if(u->ls!=NULL)
		{
			int mid=(le+re)>>1;
			u->tcnt=(u->ls->tcnt+u->rs->tcnt)%2;
			u->lcnt=u->ls->lcnt+u->ls->tcnt*((re-(mid+1)+1)-u->rs->lcnt)+(1-u->ls->tcnt)*u->rs->lcnt;
			u->rcnt=u->rs->rcnt+u->rs->tcnt*((mid-le+1)-u->ls->rcnt)+(1-u->rs->tcnt)*u->ls->rcnt;
			u->sum=(u->ls->sum+u->rs->sum)%mod;
			u->sum=(u->sum+((long long)u->ls->rcnt*((re-(mid+1)+1)-u->rs->lcnt))+((long long)((mid-le+1)-u->ls->rcnt)*u->rs->lcnt))%(long long)mod;
		}
	}
	void set(Node *u,int le,int re,int p,int val)
	{
		int mid=(le+re)>>1;
		if(le==re)	u->lcnt=u->rcnt=u->tcnt=u->sum=val;
		else
		{
			if(p<=mid)	set(u->ls,le,mid,p,val);
			else	set(u->rs,mid+1,re,p,val);
			pull(le,re,u);
		}
	}
	struct Ret
	{
		Ret()
		{
		}
		Ret(Node in,int lei,int rei)
		{
			le=lei;
			re=rei;
			lcnt=in.lcnt;
			rcnt=in.rcnt;
			tcnt=in.tcnt;
			sum=in.sum;
		}
		int le,re;
		int lcnt,rcnt,tcnt;
		int sum;
	};
	Ret merge(const Ret &a,const Ret &b)
	{
		Ret ans;
		ans.tcnt=(a.tcnt+b.tcnt)%2;
		ans.lcnt=a.lcnt+a.tcnt*((b.re-b.le+1)-b.lcnt)+(1-a.tcnt)*b.lcnt;
		ans.rcnt=b.rcnt+b.tcnt*((a.re-a.le+1)-a.rcnt)+(1-b.tcnt)*a.rcnt;
		ans.sum=(a.sum+b.sum);
		ans.sum=(ans.sum+((long long)a.rcnt*((b.re-b.le+1)-b.lcnt))+(((long long)(a.re-a.le+1)-a.rcnt)*b.lcnt))%(long long)mod;
		ans.le=a.le;
		ans.re=b.re;
		return ans;
	}
	Ret query(Node *u,int le,int re,int lc,int rc)
	{
		int mid=(le+re)>>1;
		if(le==lc&&re==rc)	return Ret(*u,le,re);
		else
		{
			if(rc<=mid)	return query(u->ls,le,mid,lc,rc);
			else
			{
				if(lc>=mid+1)	return query(u->rs,mid+1,re,lc,rc);
				else	return merge(query(u->ls,le,mid,lc,mid),query(u->rs,mid+1,re,mid+1,rc));
			}
		}
	}
}xds[10];
int n,m;
void build()
{
	for(int i=0;i<10;i++)	xds[i].r=xds[i].build(1,n,i);
}
void set(int p,int val)
{
	for(int i=0;i<10;i++)
	{
		int tmp=val%2;
		if(xds[i].sto[p]!=tmp)
		{
			xds[i].sto[p]=tmp;
			xds[i].set(xds[i].r,1,n,p,tmp);
		}
		val/=2;
	}
}
int query(int lc,int rc)
{
	int ans=0;
	for(int i=0;i<10;i++)
	{
		if(xds[i].r->sum!=0)
		ans=(ans+((long long)xds[i].query(xds[i].r,1,n,lc,rc).sum*(1<<i)))%(long long)mod;
	}
	return ans;
}
int main()
{
//	freopen("cardcaptor9.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
//	return 0;
	build();
//	return 0;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		char cmd[10];	int x,y;	 scanf("%s%d%d",cmd,&x,&y);
		if(cmd[0]=='M')	set(x,y);
		else	printf("%d\n",query(x,y));
	}
}
