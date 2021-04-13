#include<iostream>
using namespace std;
const int maxn=1100;
int n;
int hei[maxn];
int dyp[maxn][2];
int ans;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>hei[i];
	for(int i=0;i<n;i++)	dyp[i][0]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)	if(hei[j]<hei[i])	dyp[i][0]=max(dyp[i][0],dyp[j][0]+1);
		dyp[i][1]=dyp[i][0];
		for(int j=0;j<i;j++)	if(hei[j]>hei[i])	dyp[i][1]=max(dyp[i][1],dyp[j][1]+1);
		ans=max(ans,max(dyp[i][0],dyp[i][1]));
	}
//	for(int i=0;i<n;i++)	cout<<i<<" "<<dyp[i][0]<<" "<<dyp[i][1]<<endl;
	cout<<ans<<endl;
}
