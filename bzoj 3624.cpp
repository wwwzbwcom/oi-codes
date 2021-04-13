#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct Edge
{
	int u,v,c,m;
	bool operator <(Edge const &in)const
	{
		return c>in.c;
	}
}e[100100];
int n,m,k;
int kc,nc;
int fat[100100];
int find(int u)
{
	if(fat[u]==-1)	return u;
	else	return fat[u]=find(fat[u]); 
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)	scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
	sort(e+1,e+m+1);
	
	memset(fat,-1,sizeof fat);
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v;
		if(find(u)!=find(v))	fat[find(u)]=find(v),e[i].m=1;//,cout<<i<<" "<<e[i].c<<endl;
	}
	
	memset(fat,-1,sizeof fat);
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v,c=e[i].c,m=e[i].m;
		if(c==0&m==1&&find(u)!=find(v))
		{
			kc++;
			fat[find(u)]=find(v);
			e[i].m=1;
		}
		else	e[i].m=0;
	}
	if(kc>k)
	{
		printf("no solution\n");
		return 0;
	}
	
	if(kc<k)
	{
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v,c=e[i].c,m=e[i].m;
			if(c==0&m==0&&find(u)!=find(v))
			{
				kc++;
				fat[find(u)]=find(v);
				e[i].m=1;
				if(kc==k)	break;
			}
		}
	}
	if(kc<k)
	{
		printf("no solution\n");
		return 0;
	}
	
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v,c=e[i].c,m=e[i].m;
		if(c==1&m==0&&find(u)!=find(v))
		{
			nc++;
			fat[find(u)]=find(v);
			e[i].m=1;
			if(nc==n-k)	break;
		}
	}
	
	if(kc+nc==n-1)
	{
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v,c=e[i].c,m=e[i].m;
			if(m==1)	printf("%d %d %d\n",u,v,c);
		}
	}
	else	printf("no soulution\n");
}
