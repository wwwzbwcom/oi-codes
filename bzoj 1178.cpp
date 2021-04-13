#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
int n;
int lef[1000100],rig[1000100];
int sto[1000100],cnt=0;
int wei[1000100];
int dyp[1000100];
int las[1000100];
int rou[1000100];
vector <int> boo[1000100];
int mxa=0;
void output(int cur)
{
	if(las[cur]!=0)	output(las[cur]);
	if(rou[cur]==0)	cout<<rou[cur]<<endl;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>lef[i]>>rig[i],sto[cnt++]=lef[i],sto[cnt++]=rig[i];
	sort(sto,sto+cnt);
	cnt=unique(sto,sto+cnt)-sto;
	for(int i=1;i<=n;i++)
	{
		lef[i]=lower_bound(sto,sto+cnt,lef[i])-sto;
		rig[i]=lower_bound(sto,sto+cnt,rig[i])-sto;
		mxa=max(mxa,max(lef[i],rig[i]));
	}
	for(int i=1;i<=n;i++)	wei[i]=i;
//	for(int i=1;i<=n;i++)	cout<<lef[i]<<" "<<rig[i]<<" "<<wei[i]<<endl;
//	cout<<mxa<<endl;
	for(int i=1;i<=n;i++)	boo[rig[i]+1].push_back(i);
	for(int i=0;i<=mxa;i++)
	{
		if(i!=0)
		{
			dyp[i]=dyp[i-1];
			las[i]=las[i-1];
			rou[i]=0;
		}
		for(int j=0;j<boo[i].size();j++)
		{
			int p=boo[i][j];
			if(dyp[i]<dyp[lef[p]]+wei[p])
			{
				dyp[i]=dyp[lef[p]]+wei[p];
				las[i]=lef[p];
				rou[i]=p;
			}
		}
	}
	cout<<dyp[mxa]<<endl;
	output(mxa);
}
