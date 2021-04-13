#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct Bus
{
	int start;
	int delta;
	int num;
	bool operator<(const Bus &in)const
	{
		return num>in.num;
	}
}bus[100000];
int cnt=0;
int n;
int ans=2e9;
int boo[1000];
Bus newbus(int s,int d,int n)
{
	Bus ans;
	ans.start=s;ans.delta=d;ans.num=n;
	return ans;
}
bool check(int cur,int delta)
{
	for(int i=cur;i<60;i+=delta)	if(boo[i]<=0)	return 0;
	return 1;
}
void dfs(int cur,int now,int num)
{
	if(num==n)
	{
		ans=min(now,ans);
		return;
	}
	for(int i=cur;i<cnt;i++)
	{
		if(now+(n-num)/bus[i].num>=ans)	return;
		if(check(bus[i].start,bus[i].delta))
		{
			for(int j=bus[i].start;j<60;j+=bus[i].delta)	boo[j]--,num++;
			dfs(i,now+1,num);
			for(int j=bus[i].start;j<60;j+=bus[i].delta)	boo[j]++,num--;
		}
	}
}
int main()
{
	while(cin>>n)
	{
		cnt=0,ans=2e9;
		memset(boo,0,sizeof boo);
		
		int tmp;
		for(int i=1;i<=n;i++)	cin>>tmp,boo[tmp]++;
		
		for(int i=0;i<30;i++)	if(boo[i])
			for(int j=i+1;i+j<60;j++)
				if(check(i,j))
					bus[cnt++]=newbus(i,j,(59-i)/j+1);
		sort(bus,bus+cnt);
		ans=17;
		dfs(0,0,0);
		cout<<ans<<endl;
	}
}
