#include<iostream>
using namespace std;
int sto[10];
int cnt[10][10];
int dyp[10][10][1000];
void dfs1(int pos,int sta,int end,int ans)
{
	cout<<pos<<" "<<end<<endl;
	if(pos==end+1)	dyp[sta][end][cnt[sta][end]++]=ans;
	else
	{
		dfs1(pos+1,sta,end,ans+sto[pos]);
		dfs1(pos+1,sta,end,ans-sto[pos]);
		dfs1(pos+1,sta,end,ans*sto[pos]);
		if(ans%sto[pos]==0)	dfs1(pos+1,sta,end,ans/sto[pos]);
	}
}
int dfs2(int pos,int ans)
{
	if(pos==4)	cout<<ans;
	else
	{
		for(int i=0;i<4;i++)
		{
			if(pos+i+1<=4)
			{
				for(int j=0;j<cnt[pos][pos+i+1];j++)
				{
					dfs2(pos+i+1,ans+dyp[pos][pos+i+1][j]);
					dfs2(pos+i+1,ans-dyp[pos][pos+i+1][j]);
					dfs2(pos+i+1,ans*dyp[pos][pos+i+1][j]);
					dfs2(pos+i+1,ans/dyp[pos][pos+i+1][j]);
				}
			}
		}
	}
}
int main()
{
	cin>>sto[0]>>sto[1]>>sto[3]>>sto[4];
	for(int i=0;i<4;i++)
		for(int j=i;j<4;j++)
			cout<<i<<"="<<j<<endl,dfs1(i,i,j,0);
	cout<<"========"<<endl;
	dfs2(0,0);
	
	
}
