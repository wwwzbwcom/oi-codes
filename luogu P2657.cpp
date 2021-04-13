#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long ans=0;
long long n;
struct Point
{
	long long v,x;
	bool operator<(const Point in)const	{return v<in.v;}
}p[1000000];
struct SZSZ
{
	long long s[100000];
	long long len;
	void add(long long p,long long num)
	{
		for(int i=p;i<=len;i+=i&(-i))	s[i]+=num;	
	}
	long long sum(long long p)
	{
		long long ans=0;
		for(int i=p;i>0;i-=i&(-i))	ans+=s[i];
		return ans;
	}
}amo,sum;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)	scanf("%lld%lld",&p[i].v,&p[i].x);
	if(n<=8000)
	{
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans+=abs(p[i].x-p[j].x)*max(p[i].v,p[j].v);
		
	}
	else
	{
		sort(p+1,p+n+1);
	//	cout<<endl;
	//	for(int i=1;i<=n;i++)	cout<<p[i].v<<"="<<p[i].x<<endl;
	//	cout<<endl;
		amo.len=20010;
		sum.len=20010;
		for(int i=1;i<=n;i++)
		{
			long long asx=amo.sum(p[i].x-1);
			long long ssx=sum.sum(p[i].x-1);
			long long axn=amo.sum(20010)-amo.sum(p[i].x);
			long long sxn=sum.sum(20010)-sum.sum(p[i].x);
			ans+=( asx*p[i].x - ssx ) *p[i].v;
			ans+=( sxn - axn*p[i].x )*p[i].v;
		//	cout<<asx<<"="<<ssx<<" "<<axn<<"="<<sxn<<" "<<ans<<"~~~"<<amo.sum(n)<<endl;
			amo.add(p[i].x,1);
			sum.add(p[i].x,p[i].x);
		}
	}
	printf("%lld\n",ans);
}

