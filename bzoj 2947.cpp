#include<cstdio>
#include<set>
using namespace std;
multiset <int> sto;
int main()
{
	int n;	scanf("%d",&n);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int m;	scanf("%d",&m);
		for(int j=1;j<=m;j++)
		{
			int val;
			scanf("%d",&val);
			sto.insert(val);
		}
		set <int> ::iterator it=sto.end();	it--;
		ans+=*it-*sto.begin();
	//	printf("%d=%d\n",*it,*sto.begin());
		sto.erase(it);
		sto.erase(sto.begin());
	}
	printf("%lld\n",ans);
}
