#include<cstdio>
#include<algorithm>
using namespace std;
const long long maxn=1000100;
long long n,t;
long long x[maxn];
long long a[maxn];
long long lef[maxn],rig[maxn];
long long ans;
long long check(long long p,long long len)
{
	long long lp=lower_bound(x,x+n,x[p]-len)-x;
	long long rp=lower_bound(x,x+n,x[p]+len)-x;
	if(lp<1||x[lp]<x[p]-len)	lp++;
	if(rp>n||x[rp]>x[p]+len)	rp--;
	long long rem= t - ( (rig[lp]-rig[p+1]) - 2*(a[p]-a[lp-1])*(x[n]-x[p]) ) - ( (lef[rp]-lef[p-1]) - 2*(a[rp]-a[p-1])*x[p] );
	if(rem>=0)
	{
		long long ans=a[rp]-a[lp-1]; 
		long long p1=lp-1,p2=rp+1;
		if(1<=p1&&p1<=n&&1<=p2&&p2<=n&&abs(x[p]-x[p1])>abs(x[p]-x[p2]))	swap(p1,p2);
		if(1<=p1&&p1<=n)
		{
			long long tmp=min(a[p1]-a[p1-1],rem/(2*abs(x[p1]-x[p])));
			ans+=tmp;
			rem-=tmp*2*abs(x[p1]-x[p]);
		}
		if(1<=p2&&p2<=n)
		{
			long long tmp=min(a[p2]-a[p2-1],rem/(2*abs(x[p2]-x[p])));
			ans+=tmp;
			rem-=tmp*2*abs(x[p2]-x[p]);
		}
		return ans;
	}
	else return 0;
}
int main()
{
//	freopen("ex_block3.in","r",stdin);
	scanf("%lld%lld",&n,&t);
	for(long long i=1;i<=n;i++)	scanf("%lld",&x[i]);
	for(long long i=1;i<=n;i++)	scanf("%lld",&a[i]);
	for(long long i=1;i<=n;i++)	lef[i]=lef[i-1]+2*a[i]*x[i];
	for(long long i=n;i>=1;i--)	rig[i]=rig[i+1]+2*a[i]*(x[n]-x[i]);
	for(long long i=1;i<=n;i++)	a[i]=a[i-1]+a[i];
//	cout<<check(2,0)<<endl;
//	return 0;
	for(long long i=1;i<=n;i++)
	{
		long long l=0,r=1e9;
		long long ret=0;
		//cout<<i<<endl;
		while(l<=r)
		{
			long long mid=(l+r)/2,t;
			if(t=check(i,mid))	l=mid+1,ret=t;
			else				r=mid-1;
		}
		ans=max(ret,ans);
	//	cout<<i<<" "<<ret<<endl;
	}
	printf("%lld\n",ans);
}
