#include<cstdio>
using namespace std;
const long long mod=1000000007;
long long a,b,c,l,r;
long long ans;
int main()
{
	freopen("task.in","r",stdin);
	freopen("task.out","w",stdout);
	scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&l,&r);
	for(long long i=l;i<=r;i++)
	{
		long long tmp=((a*i+c)/b)%mod;
		tmp=(i*tmp)%mod;
		ans=(ans+tmp)%mod;
	}
	printf("%lld",ans);
}
