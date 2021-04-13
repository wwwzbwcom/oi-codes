#include<algorithm>
//#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
class Tree
{
	private:
		class Graph
		{
			public:
				int v,c,nxt;
				Graph()
				{
					v=c=nxt=0;
				}
		}*e;
		int n;
		int pos;
		int *pre,en;
		int getled1(int u,int f,int d)
		{
			bool flag=1;
			int ans=2e9;
			fld[u]=sld[u]=2e9;
			flu[u]=slu[u]=-1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				//int v=e[i].v,c=e[i].c;
				if(e[i].v!=f)
				{
					flag=0;
					ans=min(ans,getled1(e[i].v,u,d+e[i].c));
					int cur;
					cur=fld[e[i].v]+e[i].c;
					if(cur<fld[u])	sld[u]=fld[u],slu[u]=flu[u],fld[u]=cur,flu[u]=flu[e[i].v];
					else	if(cur<sld[u])	sld[u]=cur,slu[u]=flu[e[i].v];
					cur=sld[e[i].v]+e[i].c;
					if(cur<fld[u])	sld[u]=fld[u],slu[u]=flu[u],fld[u]=cur,flu[u]=slu[e[i].v];
					else	if(cur<sld[u])	sld[u]=cur,slu[u]=slu[e[i].v];
				}
			}
			if(flag)
			{
				int cur;
				cur=0;
				if(cur<fld[u])	sld[u]=fld[u],slu[u]=flu[u],fld[u]=cur,flu[u]=u;
				else	if(cur<sld[u])	sld[u]=cur,slu[u]=u;
			}
			if(fld[u]!=2e9&&sld[u]!=2e9)	return min(ans,fld[u]+sld[u]);
			else	return ans;
		}
		void getled2(int u,int f)
		{
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				//int v=e[i].v,c=e[i].c;
				if(e[i].v==f)
				{
					int cur;
					cur=fld[e[i].v]+e[i].c;
					if(cur<fld[u])	sld[u]=fld[u],slu[u]=flu[u],fld[u]=cur,flu[u]=flu[e[i].v];
					else	if(cur<sld[u])	sld[u]=cur,slu[u]=flu[e[i].v];
					cur=sld[e[i].v]+e[i].c;
					if(cur<fld[u])	sld[u]=fld[u],slu[u]=flu[u],fld[u]=cur,flu[u]=slu[e[i].v];
					else	if(cur<sld[u])	sld[u]=cur,slu[u]=slu[e[i].v];
				}
			}
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)	getled2(v,u);
			}
		}
		int *cnt,*fat,*lev,*dis;
		int *blo,*bll;
		void dfs1(int u,int f,int l,int d)
		{
			cnt[u]=1;	fat[u]=f;	lev[u]=l;	dis[u]=d;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)
				{
					dfs1(v,u,l+1,d+c);
					cnt[u]+=cnt[v];
				}
			}
		}
		void dfs2(int u,int f,int ff,int l)
		{
			blo[u]=ff;	bll[u]=l;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f&&cnt[v]>cnt[u]/2)	dfs2(v,u,ff,l);
			}
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f&&cnt[v]<=cnt[u]/2)	dfs2(v,u,v,l+1);
			}
		}
	public:
		int *fld,*flu;
		int *sld,*slu;
		int pass;
		void init(int ni,int posi)
		{
			n=ni;
			pos=posi;
			e=(Graph*)malloc((n+2)*2*sizeof(Graph));
			pre=(int*)malloc((n+2)*sizeof(int));
			memset(pre,-1,(n+2)*sizeof(int));
			en=0;
			
			fld=(int*)malloc((n+2)*sizeof(int));
			flu=(int*)malloc((n+2)*sizeof(int));
			sld=(int*)malloc((n+2)*sizeof(int));
			slu=(int*)malloc((n+2)*sizeof(int));
			pass=2e9;
			
			cnt=(int*)malloc((n+2)*sizeof(int));
			lev=(int*)malloc((n+2)*sizeof(int));
			dis=(int*)malloc((n+2)*sizeof(int));
			fat=(int*)malloc((n+2)*sizeof(int));
			blo=(int*)malloc((n+2)*sizeof(int));
			bll=(int*)malloc((n+2)*sizeof(int));
		}
		void erase()
		{
			free(e);
			free(pre);
			
			free(fld);
			free(flu);
			free(sld);
			free(slu);
			
			free(cnt);
			free(lev);
			free(dis);
			free(fat);
			free(blo);
			free(bll);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{	
			pass=getled1(0,-1,0);
			return;
			getled2(0,-1);
			dfs1(0,-1,0,0);
			dfs2(0,-1,0,0);
		}
		int getdis(int ui,int vi)
		{
			int u=ui,v=vi;
			while(1)
			{
				if(blo[u]==blo[v])
				{
					if(lev[u]<lev[v])	return dis[ui]+dis[vi]-2*dis[u];
					else	return dis[ui]+dis[vi]-2*dis[v]; 
				}
				else
				{
					if(bll[u]<bll[v])	v=fat[blo[v]];
					else	u=fat[blo[u]];
				}
			}
		}
}tr[400000];
long long sum[400000];
int n;
void build()
{
	sum[0]=tr[0].pass;
	for(int i=1;i<n;i++)	sum[i]=sum[i-1]+tr[i].pass;
//	for(int i=0;i<n;i++)	cout<<i<<" "<<tr[i].pass<<endl;
}
long long work(int s0,int s1,int e0,int e1)
{
	if(s0>e0)	swap(s0,e0),swap(s1,e1);
	long long ans=1e15; 
	if(s0==e0)
	{
		ans=min(ans,(long long)tr[s0].getdis(s1,e1));
		if(s0!=0)
		{
			if(tr[s0].flu[s1]!=tr[e0].flu[e1])	ans=min(ans,(long long)tr[s0-1].pass+tr[s0].fld[s1]+tr[e0].fld[e1]+2);
			else	ans=min(ans,(long long)tr[s0-1].pass+min(tr[s0].fld[s1]+tr[e0].sld[e1],tr[s0].sld[s1]+tr[e0].fld[e1])+2);
		}
		if(s0!=n-1)
		{
			if(tr[s0].flu[s1]!=tr[e0].flu[e1])	ans=min(ans,(long long)tr[s0+1].pass+tr[s0].fld[s1]+tr[e0].fld[e1]+2);
			else	ans=min(ans,(long long)tr[s0+1].pass+min(tr[s0].fld[s1]+tr[e0].sld[e1],tr[s0].sld[s1]+tr[e0].fld[e1])+2);
		} 
	}
	else
	{
		//cout<<sum[e0-1]<<" "<<sum[s0]<<" "<<tr[s0].led[s1]<<" "<<tr[e0].led[e1]<<endl;
		ans=(sum[e0-1]-sum[s0])+(e0-s0)+tr[s0].fld[s1]+tr[e0].fld[e1];
	} 
	return ans;
}
int main()
{
	//freopen("transfer5.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int mi;	scanf("%d",&mi);	tr[i].init(mi,i);
		for(int j=0;j<mi-1;j++)
		{
			int u,v,t;	scanf("%d%d%d",&u,&v,&t);
			tr[i].addedge(u,v,t);
		}
		tr[i].build();
	//	if(i==6)	return 0;
	}
	
	build();
	int q;	scanf("%d",&q);
	for(int i=0;i<q;i++)
	{
		int s0,s1,e0,e1;	scanf("%d%d%d%d",&s0,&s1,&e0,&e1);
		long long ans=work(s0,s1,e0,e1);
		if(ans<2e9)	printf("%lld\n",ans);
		else	printf("-1\n");
	}
	for(int i=0;i<n;i++)	tr[i].erase();
}
