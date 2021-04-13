#include<cmath>
#include<cstdio>
#include<algorithm> 
using namespace std;
const int maxn=100;
class Point
{
	public:
		double x,y;
		bool operator <(const Point &in)const
		{
			return x<in.x;
		}
		double getdis(const Point &in)const
		{
			return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y));
		}
}n[maxn];
int nn;
double dfs(int p,int mod,int lim)
{
	if(p==nn)	return 0;
	for(int i=p+1;i<=nn;i++)
	{
		if(mod==0)
		{
			if(n[i].y<=lim)	return dfs(i,mod,lim)+n[p].getdis(n[i]);
		}
		if(mod==1)
		{
			if(n[i].y>lim)	return dfs(i,mod,lim)+n[p].getdis(n[i]);
		}
	}
	return n[p].getdis(n[nn]);
}
int main()
{
	while(~scanf("%d",&nn))
	{
		for(int i=1;i<=nn;i++)	scanf("%lf%lf",&n[i].x,&n[i].y);
		sort(n+1,n+nn+1);
		n[0].y=-1e100;
		double ans=1e100;
		for(int i=0;i<=nn;i++)	ans=min(ans,dfs(1,0,n[i].y)+dfs(1,1,n[i].y));
		printf("%.2lf\n",ans);
	}
}
