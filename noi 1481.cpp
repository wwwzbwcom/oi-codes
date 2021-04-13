#include<iostream>
using namespace std;
int s[100000];
int lef[100000],rig[100000];
int gn,n;
int ans;
int lmax;
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n;
		ans=-2e9,lmax=-2e9;
		for(int i=1;i<=n;i++)	cin>>s[i];
		lef[0]=0;rig[n+1]=0;
		for(int i=1;i<=n;i++)	lef[i]=max(s[i],lef[i-1]+s[i]);
		for(int i=n;i>=1;i--)	rig[i]=max(s[i],rig[i+1]+s[i]);
		for(int i=1;i<=n-1;i++)
		{
			lmax=max(lmax,lef[i]);
			ans=max(ans,lmax+rig[i+1]);
		}
		cout<<ans<<endl;
	}
}
