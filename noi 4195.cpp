#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1000100;
class BCJ
{
	public:
		int fat[maxn];
		void init()
		{
			for(int i=0;i<maxn;i++)	fat[i]=i;
		}
		int find(int u)
		{
			if(u==fat[u])	return u;
			return fat[u]=find(fat[u]);
		}
		int merge(int u,int v)
		{
			if(find(u)!=find(v))	fat[find(u)]=find(v);
		}
}bc;
int gn,n;
int u[maxn],v[maxn],d[maxn];
int sto[maxn*2],sn;
int main()
{
	scanf("%d",&gn);
	for(int g=0;g<gn;g++)
	{
		scanf("%d",&n);
		sn=0;
		bc.init();
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&u[i],&v[i],&d[i]);
			sto[sn++]=u[i];
			sto[sn++]=v[i];
		}
		sort(sto,sto+sn);
		sn=unique(sto,sto+sn)-sto;
		for(int i=0;i<n;i++)
		{
			u[i]=lower_bound(sto,sto+sn,u[i])-sto;
			v[i]=lower_bound(sto,sto+sn,v[i])-sto;
		}
		int ans=1;
		for(int i=0;i<n;i++)	if(d[i]==1)	bc.merge(u[i],v[i]);
		for(int i=0;i<n;i++)	if(d[i]==0)	if(bc.find(u[i])==bc.find(v[i]))	ans=0;
		if(ans==0)	printf("NO\n");
		else	printf("YES\n");
	}
}
