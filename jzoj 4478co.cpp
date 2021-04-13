#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const long long ll=1;
const long long fix=1e10+10;
const int oo=1e9;
const int maxn=300;
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c,nxt;
				long long f;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		int flag=0;
		int dfs(int u,int lc)
		{
			if(u==end)
			{
				if(pfee-fix>0)
				{
					
					long long x=-(tfee-flo*fix)/(pfee-fix);
				//	cout<<x<<" "<<tfee<<"-"<<flo<<"*"<<fix<<" /"<<pfee<<"-"<<fix<<endl;
				//	cout<<lc<<"="<<x<<" "<<(tfee-flo*fix)<<" "<<pfee<<"-"<<fix<<" "<<tfee<<" "<<flo<<endl;
					lc=min(ll*lc,x);
					if(lc==0)	flag=1;
				}
			//	cout<<tfee<<"="<<pfee<<"="<<lc<<endl;
				tfee+=pfee*lc;
				flo+=lc;
				return lc;
			}
			vis[u]=1;
			int nc=0;
			for(int i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;	long long f=e[i].f;
				if(vis[v]==0&&c&&f==0)
				{
					int cc=min(c,lc-nc);
					cc=dfs(v,cc);
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			return nc;
		}
		bool getdis()
		{
			long long mni=ll*oo*oo;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;	long long f=e[i].f;
					if(!vis[v]&&c)	mni=min(mni,f);
				}
			if(mni==ll*oo*oo)	return 0;
			pfee+=mni;
			for(int u=1;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			return 1;
		}
	public:
		int sta,end;
		long long tfee,pfee;
		int flo;
		ZKW()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c,long long f)
		{
		//	cout<<u<<" "<<v<<" "<<c<<" "<<f<<endl;
			e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
		}
		void work()
		{
			int ans=0;
			do
			{
				int t;
				do
				{
					memset(vis,0,sizeof vis);
					t=dfs(sta,1e9);
				}while(t);
				if(flag==1)	break;
			}while(getdis());
		}
}zk;
int boo[100000];
int pri[100000],pn;
void init()
{
	boo[1]=1; 
	for(int i=2;i<100000;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=100000)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
int cnp(int val)
{
	int cnt=0;
	for(int i=1;i<=pn;i++)	while(val%pri[i]==0)	val/=pri[i],cnt++;
	return cnt;
}
int n;
int a[maxn];
int b[maxn];
int c[maxn];
int main()
{
//	freopen("pair.in","r",stdin);
//	freopen("pair.out","w",stdout);
	init();
	cin>>n;
	for(int i=0;i<n;i++)	cin>>a[i];
	for(int i=0;i<n;i++)	cin>>b[i];
	for(int i=0;i<n;i++)	cin>>c[i];
	zk.sta=n+1;	zk.end=n+2;
	for(int i=0;i<n;i++)	if(cnp(a[i])%2==0)	zk.addedge(zk.sta,i+1,b[i],0);	else	zk.addedge(i+1,zk.end,b[i],0);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)	if(i!=j)
			if(a[i]%a[j]==0&&cnp(a[i]/a[j])==1)
			{
				if(cnp(a[i])%2==0)	zk.addedge(i+1,j+1,oo,-ll*c[i]*c[j]+fix);
				else	zk.addedge(j+1,i+1,oo,-ll*c[i]*c[j]+fix);
			}
	zk.work();
	cout<<zk.flo<<endl;
	//cout<<zk.tfee-zk.flo*fix<<endl;
}
