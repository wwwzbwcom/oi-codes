#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
const int maxn=100100;
struct Point
{
	int x,y,d;
	bool operator<(const Point &in)const
	{
		if(y==in.y)	return x<in.x;
		else	return y<in.y;
	}
	
}p[maxn];
int xn,yn,n;
int ans=0;
int main()
{
	cin>>xn>>yn;
	cin>>n;
	for(int i=0;i<n;i++)	cin>>p[i].x>>p[i].y>>p[i].d;
	sort(p,p+n);
	int las=0,l,mod=1;
	for(int i=0;i<n;i++)
	{
		if(p[i].y!=las)
		{
			if(mod==0)	ans+=yn-l+1;
			las=p[i].y;
			l=1;
		}
		if(p[i].d==0)	mod=0,l=p[i].x;
		if(p[i].d==2)	mod=1,ans+=p[i].x-l+1,l=p[i].x+1;
	}
	
	for(int i=0;i<n;i++)	swap(p[i].x,p[i].y);
	sort(p,p+n);
	las=0,l,mod=1;
	for(int i=0;i<n;i++)
	{
		if(p[i].y!=las)
		{
			if(mod==0)	ans+=yn-l+1;
			las=p[i].y;
			l=1;
		}
		if(p[i].d==1)	mod=0,l=p[i].x;
		if(p[i].d==3)	mod=1,ans+=p[i].x-l+1,l=p[i].x+1;
	}
	cout<<ans<<endl;
}
