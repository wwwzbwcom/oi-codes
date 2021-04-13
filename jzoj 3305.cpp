#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=905;
const int oo=1e8;
int gn,n,m;
int sum;
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c,f,nxt;
		}e[(400*500+1000)*2];
		int pre[maxn],en=0;
		bool vis[maxn];
		int pfee;
		int dfs(int u,int lc)
		{
			if(u==end)
			{
				tfee+=lc*pfee;
				return lc;
			}
			int nc=0;
			vis[u]=1;
			for(register int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				register int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					int cc=min(lc-nc,c);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			return nc;
		}
		inline int getdis()
		{
			int mni=oo;
			for(int u=1;u<=nn;u++)	if(vis[u])
			{
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,f);
				} 
			}
			if(mni==oo)	return 0;
			pfee+=mni; 
			for(int u=1;u<=nn;u++)	if(vis[u])
			{
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			}
			return 1;
		}
	public:
		int sta,end;
		int nn;
		long long tfee;
		int flo; 
		inline void init()
		{
			memset(vis,0,sizeof vis);
			memset(pre,-1,sizeof pre);
			en=0;	pfee=0;	sta=0;	end=0;	nn=0;	tfee=0;	flo=0;
		}
		inline void addedge(int u,int v,int c,int f)
		{
			e[en].v=v;	e[en].c=c;	e[en].f= f;	e[en].nxt=pre[u];	pre[u]=en++;
			e[en].v=u;	e[en].c=0;	e[en].f=-f;	e[en].nxt=pre[v];	pre[v]=en++;
		}
		inline void zkw()
		{
			do
			{
				int t;
				do
				{
					memset(vis,0,sizeof vis);
					t=dfs(sta,oo);
					flo+=t;
				}while(t);
			}while(getdis());
		}
		inline void output()
		{
			long long ans=(tfee-(flo*(5e6+10)));
			for(int u=n+1;u<=n+m;u++)
			{
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(v==end&&c==0)
					{
						ans+=(n+m-u);
					}
				}
			}
			printf("%d\n",ans/500+sum);
			for(int u=n+1;u<=n+m;u++)
			{
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
					if(v==end&&c==0)
					{
						printf("%d ",u-n);
						break;
					}
				}
			}
			printf("\n");
		}
}zkw;
int x[maxn],y[maxn],p[maxn];
int lim[maxn],pri[maxn],rng[maxn],fin[maxn];
double getdis(int xa,int ya,int xb,int yb)
{
	return sqrt((double)((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)));
}
int main()
{
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		zkw.init();
		sum=0;
		scanf("%d%d",&n,&m);
		zkw.sta=n+m+1;	zkw.end=n+m+2;
		zkw.nn=n+m+2;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&x[i],&y[i],&p[i]);
			zkw.addedge(zkw.sta,i,1,0);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d%d%d%d",&x[n+i],&y[n+i],&lim[i],&pri[i],&rng[i],&fin[i]);
			if(fin[i])	sum+=pri[i];
			zkw.addedge(n+i,zkw.end,1,0);
		}
		for(int i=m;i>=1;i--)
			for(int j=1;j<=n;j++)
			{
				if(getdis(x[j],y[j],x[n+i],y[n+i])<=rng[i]&&p[j]<=lim[i])
				{
					if(fin[i])	zkw.addedge(j,n+i,1,-pri[i]*500ll+5e6+10-(m-i));
					else	zkw.addedge(j,n+i,1,pri[i]*500ll+5e6+10-(m-i));
				}
			}
		zkw.zkw();
		if(zkw.flo==n)	zkw.output();
		else	printf("-1\n");
	}
}
