#include<iostream>
#include<algorithm>
using namespace std;
int s[10010];
int rp[10010],fp[10010];
int min0[10010];
int main()
{
	int n;
	while(cin>>n)
	{
		for(int i=1;i<=n;i++)	cin>>s[i];
		
		int cur=0;
		for(int i=1;i<=n;i++)
		{
			int t=lower_bound(min0,min0+cur,s[i])-min0;
			if(t==cur)	cur++;
			min0[t]=s[i];
			rp[i]=t;
		}
		
	//	for(int i=1;i<=n;i++)	s[i]=-s[i];
		reverse(s+1,s+n+1);
	//	for(int i=1;i<=n;i++)	cout<<s[i]<<" ";
	//	cout<<endl;
		cur=0;
		for(int i=1;i<=n;i++)
		{
			int t=lower_bound(min0,min0+cur,s[i])-min0;
			if(t==cur)	cur++;
			min0[t]=s[i];
			fp[i]=t;
		}
		reverse(fp+1,fp+n+1);
		int ans=0;
		
	//	for(int i=1;i<=n;i++)	cout<<rp[i]<<" ";
	//	cout<<endl;
	//	for(int i=1;i<=n;i++)	cout<<fp[i]<<" ";
	//	cout<<endl;
		for(int i=1;i<=n;i++)
		{
			ans=max(ans,2*min(rp[i],fp[i])+1);
		}
		cout<<ans<<endl;
	}
}
