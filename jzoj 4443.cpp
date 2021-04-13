#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=1000100;
int n,m,k;
int a[maxn][4],b[maxn],c[maxn];
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>a[j][i];
	for(int i=0;i<n;i++)	cin>>b[i];
	for(int i=0;i<n;i++)
	{
		c[i]=0;
		for(int j=0;j<n;j++)	c[i]-=a[j][b[(i*j)%n]];
	}
	sort(c,c+n);
	cout<<-c[k-1]<<endl;
}
