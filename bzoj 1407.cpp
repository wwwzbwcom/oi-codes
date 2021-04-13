#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=20;
int n,m;
int c[maxn],p[maxn],l[maxn];
int gcd(int a,int b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
void ex_gcd(int a,int b,int &x,int &y)
{
	if(b==0)	x=1,y=0;
	else
	{
		ex_gcd(b,a%b,x,y);
		int xo=x,yo=y;
		x=yo;
		y=xo-(a/b)*x;
	}
}
int work(int a,int b,int mod,int lim)
{
	a=(a%mod+mod)%mod;	b=(b%mod+mod)%mod;
	int d=gcd(a,mod);
	if(b%d==0)
	{
		int x,y;
		ex_gcd(a,mod,x,y);
		x=((x*(b/d))%mod+mod)%mod;
		
		if(x%(mod/d)<=lim)	return 0;
		else	return 1;
	}
	else	return 1;
}
int main()
{
	scanf("%d",&n);
	int mxa=0;
	for(int i=1;i<=n;i++)	scanf("%d%d%d",&c[i],&p[i],&l[i]),mxa=max(mxa,c[i]);
	for(int k=mxa;k<=1e6;k++)
	{
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
				if(work(p[i]-p[j],c[j]-c[i],k,min(l[i],l[j]))==0)
				{
					flag=1;
					break;
				}
			if(flag==1)	break;
		}
		//cout<<k<<endl;
		if(flag==0)
		{
			m=k;
			break;
		}
	}
	printf("%d\n",m);
}
