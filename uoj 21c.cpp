#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1000100;
int n;
int poo[maxn];
int *cnt;
long long sum,cur,ans=1e16;
int main()
{
	freopen("data.in","r",stdin);
	cnt=&poo[10];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int val;	scanf("%d",&val);
		cnt[val]++;	sum+=val;
	}
	for(int i=1;i<=1e6;i++)	cnt[i]+=cnt[i-1];
	
	for(int i=1;i<=1e6;i++)
	{
		cur=sum;
		for(int j=0;j<=1e6/i;j++)
		{
			int l=j*i,r=min((int)1e6,(j+1)*i-1);
			cur-=(long long)j*(i-1)*(cnt[r]-cnt[l-1]);
		}
		ans=min(ans,cur);
	}
	printf("%lld\n",ans);
}
