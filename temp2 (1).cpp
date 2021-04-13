#include<iostream>
#include<algorithm> 
#include<set> 
using namespace std;
int n,t;
int a[10000];
set <int> b;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>a[i];
	for(int i=0;i<n;i++)	cin>>t,b.insert(t);
	sort(a,a+n);
	int ans=0;
	for(int i=0;i<n;i++)
	{
		int t=*b.begin();	
		if(a[i]<=t)
		{
			b.erase(*b.end()--);
			ans--;
		}
		else
		{
			b.erase(t);
			ans++;
		}
	}
	cout<<ans*200<<endl;
}
