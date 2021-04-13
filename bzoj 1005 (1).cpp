#include<iostream>
#include<cstring>
using namespace std;
struct bigNum
{
	int s[10000];
	int len;
	bigNum(){memset(s,0,sizeof s);len=1;}
	
	bigNum operator*(const int &in)const
	{
		bigNum ans=*this;
		int carry=0;
		for(int i=0;i<len;i++)
		{
			ans.s[i]=s[i]*in+carry;
			carry=ans.s[i]/10;
			ans.s[i]%=10;
		}
		while(carry)
		{
			ans.s[ans.len]=carry%10;
			carry/=10;
			ans.len++;
		}
		return ans;
	}
	bigNum operator/(const int &in)const
	{
		bigNum ans=*this;
		int carry=0;
		for(int i=len-1;i>=0;i--)
		{
			ans.s[i]=(s[i]+carry*10)/in;
			carry=(s[i]+carry*10)%in;
		}
		while(ans.s[ans.len-1]==0&&ans.len>1)	ans.len--;
		return ans;
	}
	void output()
	{
		for(int i=len-1;i>=0;i--)	cout<<s[i];
	}
}ans;
int n;
int deg[10000];
int cnt=0,sum=0;
int main()
{
	ans.s[0]=1;
	ans.len++;
//	ans=ans*121;
//	ans=ans*100;
//	ans=ans/12;
//	ans.output();cout<<endl;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>deg[i];
		if(deg[i]==-1)	cnt++;
		else
		{
			deg[i]--;
			sum+=deg[i];
		}
	}
	for(int i=1;i<=n-2;i++)	ans=ans*i;
	for(int i=1;i<=n;i++)	if(deg[i]!=-1)	for(int j=1;j<=deg[i];j++)	ans=ans/j;
	for(int i=1;i<=n-2-sum;i++)	ans=ans/i;
	for(int i=1;i<=n-2-sum;i++)	ans=ans*cnt;
	ans.output();
}
