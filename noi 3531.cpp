#include<iostream>
#include<cstring>
using namespace std;
const int maxn=10100;
int n,k;
int val[maxn];
int dpf[110];
int dpg[110];
int fix(int in)
{
	return (in%k+k)%k;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)	cin>>val[i];
	dpf[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<k;j++)	if(dpf[j])	dpg[fix(j+val[i])]=dpg[fix(j-val[i])]=1;
		memcpy(dpf,dpg,sizeof dpg);
		memset(dpg,0,sizeof dpg);
	}
	if(dpf[0])	cout<<"YES"<<endl;
	else	cout<<"NO"<<endl;
}
