#include<iostream>
#include<cstring>
using namespace std;
const int mod=998244353;
int gn;
int n,m;
char str[100];
int boo[100][100];
int sum=0;
int ans=0;
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=1ll*ans*ans%mod;
		if(b%2==0)	return ans;
		else	return 1ll*a*ans%mod; 
	}
}
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n>>m;
		memset(boo,0,sizeof boo);
		sum=ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>str;	int len=strlen(str);
			for(int j=0;j<len;j++)	boo[i][str[i]-'a']=1;
			sum+=len;
		}
		cin>>str;	int len=strlen(str);
		int flag=0;
		for(int i=0;i<len;i++)	if(boo[i+1][str[i]-'a']==0)
		{
			flag=1;
			break;
		}
		if(flag==0)
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=m;i>=1;i--)	ans=(ans+(long long)sum*qsm(i,mod-2)%mod)%mod,cout<<ans<<endl;
		cout<<ans<<endl;
	}
}
