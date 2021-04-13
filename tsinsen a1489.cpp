#include<cstdio>
const int maxn=100100;
int n,m;
double a[maxn],sum;
double val1,val2;
double ans1,ans2;
double pow(double a,int b)
{
	if(b==0)	return 1;
	else
	{
		double ans=pow(a,b/2);
		ans=ans*ans;
		if(b%2==0)	return ans;
		else		return ans*a;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%lf",&a[i]),sum+=a[i];
	for(int i=1;i<=n;i++)	val1+=2*(a[i]/sum)*(a[i]/sum),val2+=(a[i]/sum);
	for(int i=1;i<=m;i++)	ans1+=(i-1)*val1+val2;
	for(int i=1;i<=n;i++)	ans2+=(1.0-pow((1.0-a[i]/sum),m));
	printf("%.2lf\n%.2lf\n",ans1,ans2);
}
