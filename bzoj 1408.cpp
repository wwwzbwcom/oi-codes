#include<cstdio>
using namespace std;
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		long long ans=qsm(a,b/2);
		ans=(ans*ans)%10000;
		if(b%2==0)	return ans;
		else	return	(ans*a)%10000;
	}
}
int main()
{
	int k;	scanf("%d",&k);
	int ans1=0,ans2=0,ans3=1;
	for(int i=1;i<=k;i++)
	{
		int p,e;	scanf("%d%d",&p,&e);
		ans3=((long long)ans3*qsm(p,e))%10000;
		if(p==2)	continue;
		int t1,t2;
		t1=(ans1+(long long)(ans2+1)*(p-1))%10000;
		t2=(ans2+(long long)ans1*(p-1))%10000;
		ans1=t1;	ans2=t2;
	}
	printf("%d\n%d\n%d\n",ans2,ans1,((ans3-ans1-ans2-1)%10000+10000)%10000);
}
