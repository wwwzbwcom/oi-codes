#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200;
int n,k;
int val[maxn];
int dpf[maxn];
int dpg[maxn];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)	cin>>val[i];
	for(int i=0;i<maxn;i++)	dpf[i]=dpg[i]=-1e9;
	dpf[0]=dpg[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<k;j++)	dpg[(j+val[i])%k]=max(dpg[(j+val[i])%k],dpf[j]+val[i]);
		memcpy(dpf,dpg,sizeof dpg);
	}
	cout<<dpf[0]<<endl;
}
