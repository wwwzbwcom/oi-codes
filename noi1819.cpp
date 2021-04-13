#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n;
int sto[100];
int vis[100];
int max0,sum,ans;
int al,ag;
bool dfs(int cl,int cn)
{
	if(cn==n)	return 1;
	if(cl==al)	cl=0;
	
	for(int i=0;i<n;i++)
	{
		if(vis[i]==0&&sto[i]+cl<=al)
		{
			vis[i]=1;
			if(dfs(cl+sto[i],cn+1))	return 1;
			vis[i]=0;
			if(cl+sto[i]==al||cl==0)	return 0;
			while(sto[i]==sto[i+1])	i++;
		}
	} 
	return 0;
}
int main()
{
	while(cin>>n,n)
	{
		max0=0,sum=0,ans=0;
		for(int i=0;i<n;i++)
		{
			cin>>sto[i];
			max0=max(sto[i],max0);
			sum+=sto[i];
			sto[i]=-sto[i];
		}
		sort(sto,sto+n);
		for(int i=0;i<n;i++)	sto[i]=-sto[i];
		for(int i=max0;i<=sum;i++)
		{
			if(sum%i==0)
			{
				al=i;	ag=sum/i;
				memset(vis,0,sizeof vis);
				if(dfs(0,0))
				{
					ans=i;
					break;
				}
			}
		}
		cout<<ans<<endl;
	}
}
