#include<iostream>
#include<cmath>
using namespace std;
int n;
int x[1100],y[1100];
int mxa,mni;
inline int getdis(int i,int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
int main()
{
	cin>>n;
	mxa=0;	mni=2e9;
	for(int i=1;i<=n;i++)	cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
			{
				int tmp=getdis(i,j)+getdis(j,k)+getdis(k,i);
				if(tmp>mxa)	mxa=tmp;
				if(tmp<mni)	mni=tmp;
			}
	cout<<mxa<<endl<<mni<<endl;
}
