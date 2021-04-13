#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
int n,k;
int kn[70];
vector <int> ks[70];
int sto[1000100],sn;
vector <int> pla[1000100];
int kin[100];
int dis[1000100];
int ans=1e9;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++)
	{
		scanf("%d",&kn[i]);	int val;
		for(int j=0;j<kn[i];j++)	scanf("%d",&val),ks[i].push_back(val),sto[sn++]=ks[i][j];
	}
	sort(sto,sto+sn);
	sn=unique(sto,sto+sn)-sto;
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<kn[i];j++)	ks[i][j]=lower_bound(sto,sto+sn,ks[i][j])-sto+1,pla[ks[i][j]].push_back(i);
	}
	for(int i=1;i<=sn;i++)	dis[i]=sto[i-1];
	for(int i=0;i<100;i++)	kin[i]=0;
	for(int i=1;i<=sn;i++)
	{
		for(int j=0;j<pla[i].size();j++)	kin[pla[i][j]]=i;
		int mni=1e9,flag=0;
		for(int j=0;j<k;j++)
		{
			if(kin[j]==0)	flag=1;
			mni=min(mni,kin[j]);
		}
		if(flag==0)	ans=min(ans,dis[i]-dis[mni]);
	}
	printf("%d",ans);
}
