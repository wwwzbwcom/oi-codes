#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn=1000000;
int n;
struct Node
{
	int val,pos;
	bool operator <(const Node &in)const
	{
		return val<in.val; 
	}
}sto[maxn];
int end[maxn];
int ans=0;
struct XDS
{
	struct Node
	{
		Node()
		{
			ls=rs=NULL;
			le=re=mxa=pos=0;
		}
		Node *ls,*rs;
		int le,re;
		int mxa,pos;
	}n[maxn*3];
	int nn;
	Node *r;
	void pull(Node *u)
	{
		if(u->ls!=NULL)
		{
			if(u->ls->mxa>u->rs->mxa)	u->mxa=u->ls->mxa,u->pos=u->ls->pos;
			else	u->mxa=u->rs->mxa,u->pos=u->rs->pos;
		}
	}
	Node *build(int le,int re)
	{
		Node *u=&n[nn++];
		u->le=le;	u->re=re;
		if(le==re)
		{
			u->mxa=sto[le].val;
			u->pos=le;
		}
		else
		{
			int mid=(le+re)/2;
			u->ls=build(le,mid);
			u->rs=build(mid+1,re);
			pull(u);
		}
		return u;
	}
	struct Ret
	{
		Ret(Node *u)
		{
			mxa=u->mxa;
			pos=u->pos;
		}
		int mxa,pos;
	};
	Ret merge(const Ret &l,const Ret &r)
	{
		if(l.mxa>r.mxa)	return l;
		else	return r;
	}
	Ret maxpos(Node *u,int lc,int rc)
	{
		int le=u->le,re=u->re;
		int mid=(le+re)/2;
		if(le==lc&&re==rc)	return Ret(u);
		else
		{
			if(rc<=mid)	return maxpos(u->ls,lc,rc);
			else
			{
				if(lc>=mid+1)	return maxpos(u->rs,lc,rc);
				else	return merge(maxpos(u->ls,lc,mid),maxpos(u->rs,mid+1,rc));
			}
		}
	}
	
}xds;
inline int ReadInt()
{
	char ch = getchar();
	int data = 0;
	while (ch < '0' || ch > '9')	ch = getchar();
	do
	{
		data = data*10 + ch-'0';
		ch = getchar();
	}while (ch >= '0' && ch <= '9');
	return data;
}
int main()
{
	n=ReadInt();
	for(int i=1;i<=n;i++)	sto[i].val=ReadInt(),sto[i].pos=i;
	xds.r=xds.build(1,n);
	priority_queue <Node> que;	int p=1;
	que.push(sto[p++]);
	while(!que.empty()&&p<=n)
	{
		while(!que.empty()&&sto[p].val<que.top().val)	end[que.top().pos]=p-1,que.pop();
		que.push(sto[p++]);
	}
	while(!que.empty())	end[que.top().pos]=n,que.pop();
	
	for(int i=1;i<=n;i++)
	{
		if(end[i]-(i+1)+1<=ans)	continue;
		else	ans=max(ans,xds.maxpos(xds.r,i+1,end[i]).pos-(i+1)+1);
	}
	cout<<ans+1<<endl;
}
