#include<iostream>
using namespace std;
const int maxn=1000000;
int n,t;
int val[maxn];
int main()
{
	cin>>n>>t;
	for(int i=0;i<n;i++)	cin>>val[i];
	for(int i=0;i<t;i++)
	{
		int l,r,p;	cin>>l>>r>>p;
		int ans=0;
		for(int j=l;j<=r;j++)	ans=max(ans,val[j]%p);
		cout<<ans<<endl;
	}
} 
