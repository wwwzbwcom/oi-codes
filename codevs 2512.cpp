#include<map>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200100;
int n;
int val[maxn],cnt[maxn];
int sto[maxn],sn;
int bol[maxn],bor[maxn],bob[maxn];
int ans;
int main()
{
	cin>>n;
	sn=n;
	for(int i=0;i<n;i++)	cin>>val[i],sto[i]=val[i];
	sort(sto,sto+sn);
	sn=unique(sto,sto+sn)-sto;
	for(int i=0;i<n;i++)	val[i]=lower_bound(sto,sto+n,val[i])-sto+1;
	for(int i=0;i<n;i++)	cnt[val[i]]++;
	
	for(int i=0;i<n;i++)	cout<<i<<"="<<val[i]<<endl;
	
	bol[val[0]]++;	bor[val[0]]++;	bob[val[0]]++;	cnt[val[0]]--;	ans++;
	for(int i=1;i<n;i++)
	{
		if(bol[val[i]]&&bor[val[i]])
		{
			cnt[val[i]]--;
			continue; 
		} 
		else
		{
			if(cnt[val[i]+1]==0&&bol[val[i]+1])
			{
				if(bol[val[i]+1]==bob[val[i]+1])	bob[val[i]+1]--;
				bol[val[i]+1]--;
				bol[val[i]]++;
				cnt[val[i]]--;
				continue;
			}
			if(cnt[val[i]-1]==0&&bor[val[i]-1])
			{
				if(bor[val[i]-1]==bob[val[i]-1])	bob[val[i]-1]--;
				bor[val[i]-1]--;
				bor[val[i]]++;
				cnt[val[i]]--;
				continue;
			}
			if(bob[val[i]+1])
			{
				bob[val[i]+1]--;
				bol[val[i]+1]--;
				bol[val[i]]++;
				cnt[val[i]]--;
				continue;
			}
			if(bob[val[i]-1])
			{
				bob[val[i]-1]--;
				bor[val[i]-1]--;
				bor[val[i]]++;
				cnt[val[i]]--;
				continue;
			}
		}
		ans++;
		bol[val[i]]++;	bor[val[i]]++;	bob[val[i]]++;
		cnt[val[i]]--;
	}
	cout<<ans<<endl;
}
