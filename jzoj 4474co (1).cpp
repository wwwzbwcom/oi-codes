#include<cstdio>
using namespace std;
const int maxn=1000100;
const int mod=1e9+7;
const long long ll=1;
int gn,n,m;
int fac[maxn];
int rev[maxn];
int dyp[maxn];
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=(ll*ans*ans)%(mod);
		if(b%2==0)	return ans;
		else	return (ll*ans*a)%(mod);
	}
}
int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	fac[0]=1;	fac[1]=1;	for(int i=2;i<maxn;i++)	fac[i]=(ll*fac[i-1]*i)%(mod);
	rev[0]=1;	rev[1]=1;	for(int i=2;i<maxn;i++)	rev[i]=qsm(fac[i],mod-2);
	dyp[0]=1;	dyp[1]=0;	dyp[2]=1;	for(int i=3;i<maxn;i++)	dyp[i]=(ll*(i-1)*(dyp[i-1]+dyp[i-2]))%(mod);
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%d%d",&n,&m);
		printf("%d\n",(((ll*fac[n]*rev[n-m])%mod*rev[m])%mod*dyp[n-m])%mod);
	}
}
