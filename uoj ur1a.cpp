#include<cstdio>
#include<algorithm> 
using namespace std;
const int maxn=2100;
int n;
int val[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int in;	scanf("%d",&in);
		val[in]++;	
	}
	int ans=1e9;
	for(int i=1;i<=2000;i++)
	{
		int tmp=0;
		for(int j=1;j<=2000;j++)	tmp+=(j/i+j%i)*val[j];
	//	if(i<=10)
	//	printf("%d=%d\n",i,tmp);
		ans=min(ans,tmp);
	}
	printf("%d",ans);
}
