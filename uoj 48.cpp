#include<cstdio>
#include<map>
using namespace std;
const int maxn=1001000;
int n;
long long a[maxn];
long long gcd(long long a,long long b)
{
	if(b==0)	return a;
	else	return gcd(b,a%b);
}
int boo[maxn];
int pri[maxn],pn;
void init()
{
	boo[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
map <long long,long long> ans;
int main()
{
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		if(ans.find(a[i])!=ans.end())
		{
			printf("%lld ",ans[a[i]]);
		}
		long long g=gcd(a[i],a[1]);
		if(g==1)	ans[a[i]]=-1,printf("-1 ");
		else
		{
			
			int flag=0;
			for(int j=1;(long long)pri[j]*pri[j]<=g&&j<=pn;j++)
				if(g%pri[j]==0)
				{
					g/=pri[j];
					flag=1;
					break;
				}
			if(flag==1)	ans[a[i]]=g,printf("%lld ",g);	 
			else	ans[a[i]]=1,printf("1 ");
		}
	}
}
