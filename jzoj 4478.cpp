#include<iostream>
#include<cstdio>
using namespace std;
int n;
int a[20],b[20],c[20];
int boo[100000];
int pri[100000],pn;
void init()
{
	boo[1]=1;
	for(int i=2;i<1e5;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=1e5)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
bool isp(int val)
{
//	cout<<val<<endl;
	if(val<1e5)
	{
		if(boo[val])	return 0;
		else	return 1;
	}
	int flag=0;
	for(int i=1;pri[i]<=val&&i<=pn;i++)	while(val%pri[i]==0)	val/=pri[i],flag=1;
	if(flag)	return 0;
	else	return 1;
}
int dfs(int con,int num,int val)
{
//	cout<<con<<" "<<num<<" "<<val<<endl;
	int ans=0;
	if(val>=0)	ans=num;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)	if(i!=j)
			if(a[j]%a[i]==0&&isp(a[j]/a[i])&&(con&(1<<i))==0&&(con&(1<<j))==0)
				ans=max(ans,dfs(con|(1<<i)|(1<<j),num+1,val+c[i]*c[j]));
	return ans; 
}
int main()
{
	freopen("pair.in","r",stdin);
	freopen("pair.out","w",stdout);
	init();
	cin>>n;
	for(int i=0;i<n;i++)	cin>>a[i];
	for(int i=0;i<n;i++)	cin>>b[i];
	for(int i=0;i<n;i++)	cin>>c[i];
	cout<<dfs(0,0,0)<<endl;
}
