#include<iostream>
using namespace std;
struct SZSZ
{
	int a[100000];
	int len;
	void add(int p,int num)
	{
		for(int i=p;i<=len;i+=i&(-i))
			a[i]+=num;
	}
	int sum(int p)
	{
		int ans=0;
		for(int i=p;i>0;i-=i&(-i))
		//	cout<<i,
			ans+=a[i];
		return ans;
	}
}s;
int main()
{
	int n,m;
	cin>>n>>m;
	s.len=n;
	for(int i=1;i<=n;i++)	s.add(i,1);
	int cnt=0,cur=1;
	while(cnt<n)
	{
		int tar;
		if(s.sum(n)-s.sum(cur-1)>=m)	tar=m+s.sum(cur-1);
		else
		{
			tar=m-(s.sum(n)-s.sum(cur-1));
			tar=tar%(s.sum(n));
		}
		int ans=0;
		if(tar==0)	tar=s.sum(n);
			int l=1,r=n;
			
			while(l<=r)
			{
				int mid=(l+r)/2;
				int sm=s.sum(mid);
				if(sm==tar)	ans=mid;	
				if(sm<tar)	l=mid+1;
				else	r=mid-1;	
			}
		cout<<ans<<" ";
		s.add(ans,-1);
		cnt++;
		
		int flag=0;
		l=ans,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			int sm=s.sum(mid)-s.sum(ans-1);
			if(sm==1)	cur=mid,flag=1;
			if(sm<1)	l=mid+1;
			else	r=mid-1;
		}
		if(flag==0)
		{
			int l=1,r=n;
			while(l<=r)
			{
				int mid=(l+r)/2;
				int sm=s.sum(mid);
				if(sm==1)	cur=mid,flag=1;
				if(sm<1)	l=mid+1;
				else	r=mid-1;
			}
		}
	}
}
 
