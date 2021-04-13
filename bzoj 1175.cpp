#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n;
int sto[5100];
int mni[5100];
int idx[5100];
int pre[5100];
int ans=0;
int work()
{
	memset(mni,0,sizeof mni);
	memset(pre,-1,sizeof pre);
	int cur=0;
	for(int i=0;i<n;i++)
	{
		if(sto[i]!=0)
		{
			int t=upper_bound(mni,mni+cur,sto[i])-mni;
			if(t==cur)	cur++;
			mni[t]=sto[i];
			idx[t]=i;
			if(t>0)	pre[i]=idx[t-1];
		}
	}
	int now=idx[cur-1];
	while(
	now!=-1)
	{
		cout<<now<<" "<<sto[now]<<endl;
		sto[now]=0;
		now=pre[now];
	}
	cout<<"==================="<<endl;
	for(int i=0;i<n;i++)	cout<<sto[i]<<" ";
	cout<<endl;
	cout<<"==================="<<endl;
	return cur;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>sto[i];
	for(int i=0;i<3;i++)	ans+=work(),cout<<ans<<endl;
}
