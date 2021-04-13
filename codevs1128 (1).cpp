#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
set <int> s;
double	getdis(double x1,double y1,double x2,double y2)
{
	return	(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
struct Point
{
	int x,y;
}p[200000];
int x1,y1,x2,y2;
int n;
bool cmp1(Point a,Point b)
{
	return	getdis(a.x,a.y,x1,y1)<getdis(b.x,b.y,x1,y1);
}
bool cmp2(Point a,Point b)
{
	return	getdis(a.x,a.y,x2,y2)<getdis(b.x,b.y,x2,y2);
}
int main()
{
	cin>>x1>>y1>>x2>>y2;
	cin>>n;
	for(int i=0;i<n;i++)	cin>>p[i].x>>p[i].y;
	sort(p,p+n,cmp1);
	int r1=0,r2=0,pos=0;
	int ans=2e9;
	for(int i=0;i<n;i++)
	{
		r1=getdis(p[i].x,p[i].y,x1,y1);
		if(pos<=i)
		{
			r2=0;
			for(int j=i+1;j<n;j++)
				if(r2<getdis(p[j].x,p[j].y,x2,y2))
					pos=j,r2=getdis(p[j].x,p[j].y,x2,y2);
		}
		ans=min(r1+r2,ans);
	}
	cout<<ans<<endl;
}
