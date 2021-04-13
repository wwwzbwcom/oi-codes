#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=100100;
int gn,n,m;
struct EDGE
{
	int v,nxt;
}e[maxn*4];
int pre[maxn],en;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
long long mul[maxn];
long long val[maxn];
int cnt[maxn];
int ans[maxn],an;
map <long long,int> boo,emp;
void init()
{
	memset(pre,-1,sizeof pre);
	en=0;
	mul[0]=1;
	for(int i=1;i<maxn;i++)	mul[i]=mul[i-1]*3;
	memset(val,0,sizeof val);
	memset(cnt,0,sizeof cnt);
	an=0;
	boo=emp;
}
int main()
{
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			int u,v;	scanf("%d%d",&u,&v);
			addedge(u,v);
			cnt[u]++;	cnt[v]++;
			val[u]+=mul[v];	val[v]+=mul[u];
		//	cout<<mul[u]<<"=="<<mul[v]<<endl;
		}
		//for(int i=1;i<=n;i++)	cout<<i<<"="<<val[i]<<endl;
		for(int u=1;u<=n;u++)	boo[val[u]]++;
		for(int u=1;u<=n;u++)
		{
			if(cnt[u]==1||boo[val[u]]>1)
			{
				ans[an++]=u;
				continue;
			}
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(cnt[v]==1||val[v]-mul[u]==val[u]-mul[v])
				{
					ans[an++]=u;
					break;
				}
			}
		}
		printf("%d\n",an);
		for(int i=0;i<an;i++)	printf("%d ",ans[i]);
		printf("\n");
	}
}
