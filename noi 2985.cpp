#include<iostream>
using namespace std;
const int maxn=5000;
int n,m;
int val[maxn];
int dyp[maxn];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>val[i];
	dyp[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=m;j>=0;j--)
			dyp[j+val[i]]+=dyp[j];
	cout<<dyp[m]<<endl;
}
