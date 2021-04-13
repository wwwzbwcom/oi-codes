#include<iostream>
using namespace std;
const int maxn=20;
int n,m;
int c[maxn],p[maxn],l[maxn];
int gcd(int a,int b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
void ex_gcd(a,b,&x,&  y)
{
	if(b==0)	x=1,y=0;
	else
	{
		int xo=x,yo=y;
		x=y0;
		y=y0-(a/b)*x0;
	}
}
int work(int a,int b,int mod,int lim)
{
	a=(a%mod+mod)%mod;	b=(b%mod+mod)%mod;
	int d=gcd(a,b);
	if(b%d==0)
	{
		int x,y,ans;
		ex_gcd(a,b,x,y);
		ans=(((long long)x*(b/d))%mod+mod)%mod;
		if(ans<=lim)	return 0;
		else	return 1;
	}
	else	return 1;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>c[i]>>p[i]>>l[i],mxa=max(mxa,c[i]);
	for(int i=mxa;i<=1e6;i++)
	{
		int flag=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(work(p[i]-p[j],c[j]-c[i],i,min(l[i],l[j]))==0)
				{
					flag=1;
					break;
				}
		if(flag==0)
		{
			m=i;
			break;
		}
	}
	cout<<m<<endl;
}
