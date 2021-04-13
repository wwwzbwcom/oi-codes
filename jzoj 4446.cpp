#include<algorithm>
//#include<iostream>
#include<cstdio>
using namespace std;
int n;
int sto[1000000];
long long ans;
int bit[30];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		while(sto[i])
		{
			if(sto[i]%2==1)	bit[cnt]++;
			sto[i]/=2;
			cnt++;
		}
	}
	//for(int i=0;i<30;i++)	cout<<i<<"="<<bit[i]<<endl;
	while(1)
	{
		int mni=1e9;
		for(int i=0;i<30;i++)	if(bit[i]!=0)	mni=min(mni,bit[i]);
		if(mni==1e9)	break;
		int cur=0;
		for(int i=0;i<30;i++)	if(bit[i]>=mni)	bit[i]-=mni,cur+=(1<<i);
		ans+=(long long)mni*cur*cur;
	}
	printf("%lld",ans);
}
