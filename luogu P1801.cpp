#include<algorithm>
//#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
struct SZSZ
{
	int s[500100];
	int len;
	void add(int p,int num)
	{
		for(int i=p;i<=len;i+=i&(-i))	s[i]+=num;
	}
	int sum(int p)
	{
		int ans=0;
		for(int i=p;i>0;i-=i&(-i))	ans+=s[i]; 
		return ans;
	}
}s;
map <int,int> idx;
int m,n;
int a[200100],tmp[200100],b[200100];
int main()
{
	s.len=200100;
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)	scanf("%d",&a[i]),tmp[i]=a[i];
	sort(tmp,tmp+m);
	int cnt=unique(tmp,tmp+m)-tmp;
	for(int i=0;i<m;i++)
	{
		int t=lower_bound(tmp,tmp+cnt,a[i])-tmp+1;
		idx[t]=a[i];
		a[i]=t;
	}
	for(int i=0;i<n;i++)	scanf("%d",&b[i]);
	
	int cur=0;
	for(int i=0;i<m;i++)
	{
		s.add(a[i],1);
		while(i==b[cur]-1)
		{
			cur++;
			int l=0,r=200000;
			int	ans=-1;
			while(l<=r)
			{
				int mid=(l+r)/2;
			//	cout<<l<<"="<<r<<" "<<s.sum(mid)<<"="<<s.sum(mid-1)<<endl;
				if(s.sum(mid-1)>=cur)	r=mid-1;
				else
				{
					ans=mid;
					l=mid+1;
				}
			}
			printf("%d\n",idx[ans]);
		//	cout<<idx[ans]<<" "<<ans<<" "<<s.sum(100)<<" "<<cur<<endl;
		}
	}
}
