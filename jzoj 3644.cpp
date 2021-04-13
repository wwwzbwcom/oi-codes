#include<algorithm>
//#include<iostream>
#include<cstdio>
#include<cmath>
#include<set>
#include<map>
using namespace std;
const int maxn=100100;
int n,m;
int boo[2][maxn];
set <int> dou;
int sto[maxn];
int bl,blo[maxn];
int ans[maxn];
int mar[maxn],pri[maxn],pn;
int buc[maxn],bn;
int cnt[maxn];
int lis[maxn][30],lin[maxn];
void dfs(int p,int cur,int pos)
{
	if(p==bn)	lis[pos][lin[pos]++]=cur;
	else
	{
		dfs(p+1,cur,pos);
		int tmp=1;
		for(int i=1;i<=cnt[p];i++)	tmp*=buc[p],dfs(p+1,cur*tmp,pos);
	}
}
void init()
{
	mar[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(mar[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			mar[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
	for(int k=1;k<maxn;k++)
	{
		bn=0;
		int tmp=k;
		for(int i=1;i<=pn&&pri[i]<=tmp;i++)
		{
			if(tmp%pri[i]==0)
			{
				buc[bn]=pri[i];	cnt[bn]=0;
				while(tmp%pri[i]==0)	cnt[bn]++,tmp/=pri[i];
				bn++;
			}
		}
		lin[k]=0;
		dfs(0,1,k);
	} 
	
}
class Query
{
	public:
		int le,re;
		int pos;
		bool operator <(const Query &in)const
		{
			if(blo[le]==blo[in.le])	return re<in.re;
			return le<in.le;
		}
}q[maxn];

int jishu;
inline void opt(int val,int mod1,int mod2)
{
	if(mod1==1)
	{
		for(int i=0;i<lin[val];i++)
		{
			int cur=lis[val][i];
			boo[mod2][cur]++;
			if(boo[mod2][cur]>0&&boo[mod2^1][cur]>0)	dou.insert(cur);
		}
	}
	else
	{
		for(int i=0;i<lin[val];i++)
		{
			int cur=lis[val][i];
			boo[mod2][cur]--;
			if(boo[mod2][cur]<=0)	dou.erase(cur);
		}
	}
}
int main()
{
//	freopen("eat3.in","r",stdin);
//	freopen("out.txt","w",stdout);
	init();
	//for(int i=1;i<=10;i++)	cout<<i<<" "<<pri[i]<<endl;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	bl=sqrt(n);
	for(int i=1;i<=n;i++)	blo[i]=(i-1)/bl+1;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].le,&q[i].re);
		q[i].pos=i;
	}
	sort(q+1,q+m+1);
	int lc=1,rc=0;
	for(int i=1;i<=n;i++)	opt(sto[i],1,1);
	for(int i=1;i<=m;i++)
	{
		while(lc<q[i].le)	opt(sto[lc],0,0),opt(sto[lc],1,1),lc++;
		while(lc>q[i].le)	lc--,opt(sto[lc],1,0),opt(sto[lc],0,1);
		while(rc<q[i].re)	rc++,opt(sto[rc],1,0),opt(sto[rc],0,1);
		while(rc>q[i].re)	opt(sto[rc],0,0),opt(sto[rc],1,1),rc--;
		if(dou.begin()==dou.end())	ans[q[i].pos]=0;
		else
		{
			set <int> ::iterator it=dou.end();	it--;
			ans[q[i].pos]=(*it);
		}
	}
	printf("%d",jishu);
	for(int i=1;i<=m;i++)	printf("%d\n",ans[i]);
}
