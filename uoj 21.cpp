#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100100;
int n;
int sto[maxn];
int chu[2100][2100];
int mod[2100][2100];
int cnt[2100];
int ans=1e9;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int val;	scanf("%d",&val);
		cnt[val]++;
	}
	for(int i=1;i<=2000;i++)
		for(int j=0;j<=2000;j++)
		{
			chu[i][j]=j/i;
			mod[i][j]=j%i;
		}
	for(int i=1;i<=2000;i++)
	{
		int cur=0;
		for(int j=0;j<=2000;j++)
		{
			cur+=(chu[i][j]+mod[i][j])*cnt[j];
			if(cur>=ans)	break;
		}
	//	cout<<i<<" "<<cur<<endl;
		ans=min(ans,cur);
	}
	printf("%d",ans);
}
