#include<iostream>
using namespace std;
const int maxn=1010;
int n;
int val[maxn];
int dyp[maxn];
int ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>val[i];
	for(int i=1;i<=n;i++)	dyp[i]=val[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i-1;j++)
			if(val[j]<val[i])
				dyp[i]=max(dyp[i],dyp[j]+val[i]);
	for(int i=1;i<=n;i++)	ans=max(ans,dyp[i]),cout<<i<<" "<<dyp[i]<<endl;
	cout<<ans<<endl;
}
