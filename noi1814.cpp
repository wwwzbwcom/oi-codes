#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
struct Point
{
	int x,y;
	bool operator<(const Point &in)const
	{
		if(x==in.x)	return y<in.y;
		return x<in.x;
	}
}p[5001];
int xn,yn;
int boo[5001][5001];
int n;
int ans=0;
bool inmap(int x,int y)
{
	if(0<x&&x<=xn&&0<y&&y<=yn)	return 1;
	else	return 0;
}
int main()
{
	cin>>xn>>yn;
	cin>>n;
	for(int i=0;i<n;i++)	cin>>p[i].x>>p[i].y,boo[p[i].x][p[i].y]=1;
	sort(p,p+n);
	
	ans=2;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			int xi=p[i].x,yi=p[i].y;
			int xj=p[j].x,yj=p[j].y;
			int	xd=xj-xi,yd=yj-yi;
			int xc=xi,yc=yi;
			
			if(xd==0&&yd==0)	continue;
			if(inmap(xi-xd,yi-yd))	continue;
			if(!inmap(xi+ans*xd,yi+ans*yd))	continue;
			cout<<xi<<" "<<yi<<" "<<xi+ans*xd<<" "<<yi+ans*yd<<endl;
			int cur=0;
			while(0<xc&&xc<=xn&&0<yc&&yc<=yn&&boo[xc][yc]==1)	cur++,xc+=xd,yc+=yd;
			if(0<xc&&xc<=xn&&0<yc&&yc<=yn);	else	ans=max(cur,ans);
		}
	if(ans<3)	cout<<0<<endl;
	else	cout<<ans<<endl;
}
