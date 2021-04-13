#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
#define ll long long

long long x,y;
int ex_gcd(int a,int b)
{
	int ans;
	if(b==0)
	{
		x=1;y=0;
		return	a;
	}
	else	ans=ex_gcd(b,a%b);
	int xt=x,yt=y;
	x=yt;	y=xt-(a/b)*yt;
	return ans;
}

int xx[2],yy[2];
int f[2];

int calc1(int a,int b,int d1,int d2,int v)
{
	int d = f[0];
	if(v%d) return 0;
	ll x= xx[0],y = yy[0];
	x *= v/d; y *= v/d;
	a /= d; b /= d;
	int up = min(floor(double(x)/b) , floor(double(d2-y)/a)); 
	int  down = max(ceil(double(x-d1)/b) , ceil(double(-y)/a));
	return up<down?0:(up-down+1);
}

int calc2(int a,int b,int d1,int d2,int v)
{
	int d = f[1];
	if(v%d) return 0;
	ll x= xx[1],y = yy[1];
	x *= v/d; y *= v/d;
	a /= d; b /= d;
	int up = min(floor(double(x)/b) , floor(double(d2-y)/a)); 
	int down = max(ceil(double(x-d1)/b) , ceil(double(-y)/a));
	return up<down?0:(up-down+1);
}

int main()
{
	int c1,c2,c3,c4,tot;
	scanf("%d%d%d%d%d",&c1,&c2,&c3,&c4,&tot);
	f[0] = ex_gcd(c1,c2); xx[0] = x, yy[0] = y;
	f[1] = ex_gcd(c3,c4); xx[1] = x, yy[1] = y;
	while(tot--)
	{
		int d1,d2,d3,d4,s;
		scanf("%d%d%d%d%d",&d1,&d2,&d3,&d4,&s);
        long long ans = 0; 
		for(int i=0;i<=s;i+=f[0])	
		{
	//		cout<<i<<" "<<calc1(c1,c2,d1,d2,i)<<endl;
			ans += calc1(c1,c2,d1,d2,i) * calc2(c3,c4,d3,d4,s-i);
		}
		printf("%lld\n",ans);
	}
}
