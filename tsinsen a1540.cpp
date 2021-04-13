#include<iostream>
using namespace std;
const int maxn=100100;
int n;
int x,a,b;
long long m,t,sum;
long long cur;
int ans[maxn];
int main()
{
	scanf("%d",&n);
	scanf("%d%d%d%lld",&x,&a,&b,&m);
	for(int i=0;i<=n-1;i++)	t+=x+(long long)a*i;
	sum=(t-m)/(a+b);
	for(int i=n-1;i>=1;i--)
	{
		if(sum-i>=0)	sum-=i,ans[i]=-1;
		else			ans[i]=1;
	}
	cur=x;
	printf("%lld ", cur);
	for(int i=2;i<=n;i++)
	{
		if(ans[n-i+1]==1)	cur+=a;
		if(ans[n-i+1]==-1)	cur-=b;
		printf("%lld ", cur);
	}
}
