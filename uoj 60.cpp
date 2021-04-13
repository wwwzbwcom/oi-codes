#include<cstdio>
using namespace std;
const int mod=998244353;
int n;
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=((long long)ans*ans)%mod;
		if(b%2)	return ((long long)ans*a)%mod;
		else	return ans;
	}
}
int main()
{
	scanf("%d",&n);
	printf("%d\n",(qsm(3,n-1)*4ll)%mod);
	for(int i=1;i<=n;i++)	printf("A 0 0 0 0\n");
}
