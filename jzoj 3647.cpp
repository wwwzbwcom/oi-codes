#include<cstdio>
#include<map>
using namespace std;
const int maxn=7100;
class SUB
{
	public:
		int sid,cid,pid,uid,res;
};
map <int,SUB> su;
class XDS
{
	private:
		class NOD
		{
			public:
				int le,re;
				int ls,rs;
				int sum;
		}n[maxn];
		int nn;
		void pull(int u)
		{
			if(n[u].ls!=0)	n[u].sum=n[n[u].ls].sum+n[n[u].rs].sum;
		}
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn;
			n[u].le=le;	n[u].re=re;
			if(le!=re)
			{
				int mid=(le+re)/2;
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
			}
			return u;
		}
		void optadd(int u,int pos,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)	n[u].sum+=val;
			else
			{
				int mid=(le+re)/2;
				if(pos<=mid)	optadd(n[u].ls,pos,val);
				else	optadd(n[u].rs,pos,val);
				pull(u);
			}
		}
		int qrysum(int u,int lc,int rc)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2; 
			if(le==lc&&re==rc)	return n[u].sum;
			else
			{
				int ans=0;
				if(rc<=mid)	ans=qrysum(n[u].ls,lc,rc);
				else
				{
					if(lc>=mid+1)	ans=qrysum(n[u].rs,lc,rc);
					else	ans=qrysum(n[u].ls,lc,mid)+qrysum(n[u].rs,mid+1,rc);
				}
				//cout<<lc<<" "<<rc<<" "<<ans<<endl;
				return ans; 
			}
		}
};
class CON
{
	public:
		CON()
		{
			xd.r=xd.build(0,1100);
		}
		XDS xd;
		int exi[maxn],n;
		map <int,int> cnt[maxn];
		void getrnk(int uidi)
		{
			int num=cnt[uidi].size();
			printf("%d %d %d %d\n",uidi,num,xd.qrysum(xd.r,num+1,1100)+1,xd.qrysum(xd.r,num,1100));
		}
}co[60];
void chgres(int sidi,int cidi,int pidi,int uidi,char *resi)
{
	if(resi[0]=='A')
	{
		int bef=co[cidi].cnt[uidi].size();
		co[cidi].cnt[uidi][pidi]++;
		int aft=co[cidi].cnt[uidi].size();
		
		if(co[cidi].exi[uidi]==1)
		co[cidi].xd.optadd(co[cidi].xd.r,bef,-1);
		
		co[cidi].xd.optadd(co[cidi].xd.r,aft, 1);
	}
	else	if(co[cidi].exi[uidi]==0)	co[cidi].xd.optadd(co[cidi].xd.r,0,1); 
	if(co[cidi].exi[uidi]==0)	co[cidi].exi[uidi]=1,co[cidi].n++;//co[cidi].xd.optadd(co[cidi].xd.r,0,1);
	su[sidi].sid=sidi;
	su[sidi].cid=cidi;
	su[sidi].pid=pidi;
	su[sidi].uid=uidi;
	if(resi[0]=='A')	su[sidi].res=1;	else	su[sidi].res=0;
}
void chgwai(int sidi)
{
	if(su[sidi].res==1)
	{
		int cidi=su[sidi].cid,pidi=su[sidi].pid,uidi=su[sidi].uid;
		int bef=co[cidi].cnt[uidi].size();
		co[cidi].cnt[uidi][pidi]--;
		if(co[cidi].cnt[uidi][pidi]==0)	co[cidi].cnt[uidi].erase(pidi);
		int aft=co[cidi].cnt[uidi].size();
		co[cidi].xd.optadd(co[cidi].xd.r,bef,-1);
		co[cidi].xd.optadd(co[cidi].xd.r,aft, 1);
	}
	su[sidi].res=0;
}
int main()
{
//	freopen("oj3.in","r",stdin);
	int t1,t2,m;	scanf("%d%d%d",&t1,&t1,&m);
	for(int i=1;i<=m;i++)
	{
		//cout<<i<<endl;
		char cmd[20];	scanf("%s",cmd);
		int sid,cid,pid,uid;	char res[20];
		if(cmd[0]=='c')
		{
			scanf("%d%d",&t1,&t1);
			for(int j=1;j<=t1;j++)	scanf("%d",&t2);
		}
		if(cmd[0]=='s')
		{
			scanf("%d%d%d%d%s",&sid,&cid,&pid,&uid,res);
			chgres(sid,cid,pid,uid,res);
		}
		if(cmd[0]=='g')
		{
			scanf("%d%d",&cid,&uid);
			co[cid].getrnk(uid);
		}
		if(cmd[0]=='r')
		{
			scanf("%d",&sid);
			chgwai(sid);
		}
	}
}
