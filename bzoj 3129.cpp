#include<cstdio>
#include<cmath>
//#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100100;
const double pi=atan(1)*4;
struct Point
{
	int x,y;
	double deg;
	bool operator <(const Point &in)const
	{
		return deg<in.deg;
	}
}p[maxn];
int n,mid;
int cur;
long long ans;
long long c[maxn][4]; 
void init()
{
	c[0][0]=1;
	c[1][0]=1;	c[1][1]=1;
	c[2][0]=1;	c[2][1]=2;	c[2][2]=1;
	for(int i=3;i<maxn;i++)
	{ 
		c[i][0]=1;
		for(int j=1;j<=3;j++)	c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
}
int main()
{
	
	freopen("tricount10.in","r",stdin);
	init();
	scanf("%d",&n);
//	cout<<(long long)n*(n-1)*(n-2)/6<<" "<<c[n][3]<<endl;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y),p[i].deg=atan2(p[i].y+0.0,p[i].x+0.0);
		if(p[i].deg<0)	p[i].deg=p[i].deg+2*pi;
	}
	sort(p+1,p+n+1);
//	for(int i=1;i<=n;i++)	cout<<p[i].x<<"="<<p[i].y<<"="<<p[i].deg<<endl;
	for(int i=1;i<=n;i++)
		if(p[i].y<0)
		{
			mid=i;
			break;
		}
	ans=c[n][3];
//	cout<<(long long)n*(n-1)*(n-2)/6<<endl;
//	cout<<ans<<endl;
	int p2=mid;
	cur=mid-1;
	for(int p1=1;p1<mid;p1++)
	{
		cur--;
		while(p2<=n&&p[p2].deg-pi<=p[p1].deg)	p2++,cur++;
	//	cout<<p1<<" "<<p2<<" "<<cur<<endl;
		ans-=c[cur][2];
	}
	
//	cout<<ans<<endl;
	p2=1;
	cur=n-mid+1;
	for(int p1=mid;p1<=n;p1++)
	{
		cur--;
		while(p2<mid&&p[p2].deg+pi<=p[p1].deg)	p2++,cur++;
	//	cout<<p1<<" "<<p2<<" "<<p[p1].deg<<" "<<p[p2].deg<<" "<<cur<<endl;
		ans-=c[cur][2];
	}
	printf("%lld",ans);
}
