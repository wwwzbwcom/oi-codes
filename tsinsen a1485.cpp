#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=60100;
int n,q;
int ans[maxn];
struct OPERATE
{
	 double t,x,y,z;
	 bool operator <(const OPERATE &in)const
	 {
	 	return t<in.t;
	 }
}opt[maxn];
struct QUERY
{
	double t,x,y,z;
	int p;
	bool operator <(const QUERY &in)const
	{
		return t<in.t;
	}
}qry[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%lf%lf%lf%lf",&opt[i].t,&opt[i].x,&opt[i].y,&opt[i].z);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)	scanf("%lf%lf%lf%lf",&qry[i].t,&qry[i].x,&qry[i].y,&qry[i].z),qry[i].p=i;
//	puts("=======");
	sort(opt+1,opt+1+n);
	sort(qry+1,qry+1+q);
	for(int i=1;i<=q;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(opt[j].t>qry[i].t)	break;
			if(qry[i].x>=opt[j].x&&qry[i].y>=opt[j].y&&qry[i].z>=opt[j].z)	ans[qry[i].p]++; 
		}
	}
	for(int i=1;i<=q;i++)	printf("%d\n",ans[i]);
}

