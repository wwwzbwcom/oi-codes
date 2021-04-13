#include<algorithm>
#include<cstdio>
using namespace std;
int dyp[1000100];
int bit[100];
int main()
{
	int n;	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int val;	scanf("%d",&val);
		int cnt=0;
		while(val)
		{
			if(val%2==1)
			{
				dyp[i]=dyp[bit[cnt]]+1;
				bit[cnt]=i;
			}
			val/=2;
			cnt++;
		}
		ans=max(ans,dyp[i]);
	}
	printf("%d",ans);
}
