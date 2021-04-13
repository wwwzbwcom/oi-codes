#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Point
{
	int num,place;
	bool operator<(const Point in)const
	{
		return num<in.num;
	}
}p[3000000];
struct SZSZ
{
	int a[3000000];
	int n; 
	void add(int p,int num)
	{
		for(int i=p;i<=n;i+=(i&(-i)))	a[i]+=num;
	}
	int sum(int p)
	{
		int ans=0;
		for(int i=p;i>0;i-=(i&(-i)))	ans+=a[i];
		return ans;
	}
}s;
int n;
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&p[i].num),p[i].place=i;
	sort(p+1,p+n+1);
	s.n=n;
	for(int i=1;i<=n;i++)	s.add(i,1);
}
int main()
{
	init();
	
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int le=p[i].place,re=p[i].place;
		int cur=p[i].place;
		
		int l=0,r=p[i].place;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(s.sum(mid)-s.sum(cur-1)==(mid-cur+1))	le=mid,l=mid+1;
			else	r=mid-1;
		}
		
		l=p[i].place,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(s.sum(mid)-s.sum(cur-1)==(mid-cur+1))	re=mid,l=mid+1;
			else	r=mid-1;
		}
		ans=max(ans,(re-le+1)*(long long)p[i].num);
		
	//	cout<<p[i].num<<" "<<p[i].place<<" "<<le<<" "<<re<<" "<<(re-le+1)*p[i].num<<endl;
		s.add(p[i].place,-1);
	}
	printf("%lld",ans);
}
