#include<cstdio>
#include<map>
using namespace std;
map <int,int> dyp[2100];
int sto[2100];
int ans=0;
int main()
{
	int n;	scanf("%d",&n);
	if(n==1)	printf("%d",1);
	else
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&sto[i]);
			for(int j=1;j<i;j++)	dyp[i][sto[j]]=max(2,dyp[j][sto[j]-(sto[i]-sto[j])]+1),ans=max(ans,dyp[i][sto[j]]);
		}
		printf("%d",ans);
	}
}
