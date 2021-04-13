#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const long double oo=1e4000;
long double w,h,d;
struct Point
{
	long double x,y;
	void build(long double xi,long double yi)
	{
		x=xi;	y=yi;
	}
	Point rotate(long double deg)
	{
		Point ans;
		long double r=sqrt(x*x+y*y);
		if(y>0)	deg+=acos(x/r);	else	deg-=acos(x/r);
	//	cout<<deg<<" "<<x<<" "<<y<<" "<<cos(deg)*r<<endl;
	//	cout<<deg<<endl;
		ans.x=cos(deg)*r;
		ans.y=sin(deg)*r; 
		return ans;
	}
}pb[4],pa[4];
struct Line
{
	Point s,e;
	long double k,b;
	void build(Point si,Point ei)
	{
		s=si;	e=ei;
		k=(s.y-e.y)/(s.x-e.x);
		b=s.y-k*s.x;
	}
	Point getxj(Line const &in)const
	{
		Point ans;
		
		if(k>=oo||k<=-oo||in.k>=oo||in.k<=-oo)
		{
		//	cout<<"==="<<endl;
		//	cout<<k<<" "<<in.k<<endl;
			if(k>=oo||k<=-oo)
			{
				ans.x=s.x;
				ans.y=s.x*in.k+in.b;
			}
			else
			{
				ans.x=in.s.x;
				ans.y=in.s.x*k+b;
			}
		}
		else
		{
			ans.x=(in.b-b)/(k-in.k);
			ans.y=k*ans.x+b;
		}
		return ans; 
	}
	bool judgexj(Line const &in)const
	{
		Point ans=getxj(in);
		if(min(s.x,e.x)-1e-10<=ans.x&&ans.x<=max(s.x,e.x)+1e-10)
			if(min(s.y,e.y)-1e-10<=ans.y&&ans.y<=max(s.y,e.y)+1e-10)
				if(min(in.s.x,in.e.x)-1e-10<=ans.x&&ans.x<=max(in.s.x,in.e.x)+1e-10)
					if(min(in.s.y,in.e.y)-1e-10<=ans.y&&ans.y<=max(in.s.y,in.e.y)+1e-10)
						return 1; 
		return 0;
	}
}lb[4],la[4];
int main()
{
//	cout<<1/0.0<<endl;
//	cout<<oo<<endl;
//	cout<<sin(6.28)<<endl;
	cin>>w>>h>>d;
	if(w<h)	swap(w,h);
	if(d==0||d==180)
	{
		printf("%.10lf",(double)(w*h));
		return 0;
	}
	d=(d/180)*atan(1)*4;
	pb[0].build(-w/2, h/2);
	pb[1].build( w/2, h/2);
	pb[2].build( w/2,-h/2);
	pb[3].build(-w/2,-h/2);
	for(int i=0;i<4;i++)	pa[i]=pb[i].rotate(d);
//	for(int i=0;i<4;i++)	cout<<i<<" "<<pb[i].x<<"="<<pb[i].y<<" "<<pa[i].x<<"="<<pa[i].y<<endl; 
	for(int i=0;i<4;i++)	lb[i].build(pb[i],pb[(i+1)%4]);
	for(int i=0;i<4;i++)	la[i].build(pa[i],pa[(i+1)%4]);
//	for(int i=0;i<4;i++)	cout<<lb[i].k<<" "<<lb[i].b<<endl;
//	for(int i=0;i<4;i++)	cout<<la[i].k<<" "<<la[i].b<<endl;
//	cout<<la[0].getxj(lb[0]).x<<" "<<la[0].getxj(lb[0]).y<<" "<<la[0].judgexj(lb[0])<<endl;
//	cout<<la[0].getxj(lb[3]).x<<" "<<la[0].getxj(lb[3]).y<<" "<<la[0].judgexj(lb[3])<<endl;
	if(la[0].judgexj(lb[0])&&la[0].judgexj(lb[3]))
	{
		long double ans=0;
		ans+=abs(-w/2-la[0].getxj(lb[0]).x)*abs( h/2-la[0].getxj(lb[3]).y)/2;
		ans+=abs( w/2-la[1].getxj(lb[0]).x)*abs( h/2-la[1].getxj(lb[1]).y)/2;
		ans+=abs( w/2-la[2].getxj(lb[2]).x)*abs(-h/2-la[2].getxj(lb[1]).y)/2;
		ans+=abs(-w/2-la[3].getxj(lb[2]).x)*abs(-h/2-la[3].getxj(lb[3]).y)/2;
		printf("%.10lf",(double)(w*h-ans));
		return 0;
	}
	if(la[0].judgexj(lb[0])&&la[0].judgexj(lb[2]))
	{
	//	cout<<"=="<<endl;
		long double ans=0;
		ans+=(abs(-w/2-la[0].getxj(lb[0]).x)+abs(-w/2-la[0].getxj(lb[2]).x))*h/2;
		ans+=(abs( w/2-la[2].getxj(lb[0]).x)+abs( w/2-la[2].getxj(lb[2]).x))*h/2;
		printf("%.10lf",(double)(w*h-ans));
		return 0;
	}
	if(la[0].judgexj(lb[2])&&la[0].judgexj(lb[3]))
	{
	//	cout<<"===="<<endl;
		long double ans=0;
		ans+=abs(-w/2-la[1].getxj(lb[0]).x)*abs( h/2-la[1].getxj(lb[3]).y)/2;
	//	cout<<ans<<" "<<la[3].getxj(lb[0]).x<<" "<<la[3].getxj(lb[0]).y<<endl;
		ans+=abs( w/2-la[2].getxj(lb[0]).x)*abs( h/2-la[2].getxj(lb[1]).y)/2;
		ans+=abs( w/2-la[3].getxj(lb[2]).x)*abs(-h/2-la[3].getxj(lb[1]).y)/2;
		ans+=abs(-w/2-la[0].getxj(lb[2]).x)*abs(-h/2-la[0].getxj(lb[3]).y)/2;
		printf("%.10lf\n",(double)(w*h-ans));
	//	cout<<w*h<<" "<<ans<<endl;
		return 0;
	}
//	cout<<"=="<<endl;
}
