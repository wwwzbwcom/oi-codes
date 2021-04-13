#include<iostream>
using namespace std;
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;cin>>x>>y;
		ans+=y;ans-=x;
	}
	for(int i=1;i<=n;i++)
	{
		int x,y;cin>>x>>y;
		ans-=y;ans+=x;
	}
	cout<<ans;
}
