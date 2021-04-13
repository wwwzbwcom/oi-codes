#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=6000;
int n,x;
int a[maxn];
int dyp[maxn];
int ans;
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)	cin>>a[i],a[i]=-a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)	a[i]=-a[i];
	
//	for(int i=1;i<=n;i++)	cout<<i<<" "<<a[i]<<endl;
	
	dyp[x]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=x;j++)
			if(dyp[j])
				dyp[j%a[i]]=1;
	
	for(int i=0;i<=x;i++)	if(dyp[i])	ans=max(ans,i%a[n]);
	cout<<ans<<endl<<0<<endl;
}
