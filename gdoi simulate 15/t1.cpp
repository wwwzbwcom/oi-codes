#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int sto[1000];
int dyp[1000][30][2];
int getans(int l,int r,int k)
{
	memset(dyp,0,sizeof dyp);
	for(int i=l;i<=r;i++)
		for(int j=1;j<=k;j++)
		{
			dyp[i][j][0]=max(dyp[i-1][j][0],dyp[i-1][j][1]);
			dyp[i][j][1]=max(dyp[i-1][j-1][0]+sto[i],dyp[i-1][j][1]+sto[i]);
		}
	int ans=0;
	for(int i=0;i<=k;i++)
	{
	//	cout<<i<<" "<<dyp[r][i][0]<<" "<<dyp[r][i][1]<<endl;
		ans=max(ans,max(dyp[r][i][0],dyp[r][i][1]));
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>sto[i];
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int cmd;	cin>>cmd;
		if(cmd==0)
		{
			int pos,val;	cin>>pos>>val;
			sto[pos]=val;
		}
		if(cmd==1)
		{
			int l,r,k;	cin>>l>>r>>k;
			cout<<getans(l,r,k)<<endl;
		}
	}
}
