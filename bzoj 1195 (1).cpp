#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
int n;
string str[20];
int vis[20];
int mni=1e8;
string ans;
string mer(string a,string b)
{
	for(int i=0;i<(int)a.size()-(int)b.size();i++)
		if(a.substr(i,b.size())==b)
			return a;
	string tmp;
	int len=a.size()-max(0,(int)a.size()-(int)b.size());
	for(int i=max(0,(int)a.size()-(int)b.size());i<a.size();i++)
	{
	//	cout<<a.substr(i,len)<<"="<<b.substr(0,len)<<" "<<len<<endl;
		if(a.substr(i,len)==b.substr(0,len))
			return a+b.substr(len,b.size()-len);
		len--;
	}
	return a+b;
}
void dfs(int u,string s)
{
	
	if(u==n)
	{
		if((int)s.size()<mni)
		{
			mni=s.size();
			ans=s;
		}
		else	if((int)s.size()==mni)	ans=min(ans,s);
		return;
	}
	if((int)s.size()>mni)	return;
	for(int i=0;i<n;i++)
	{
		if(vis[i]==0)
		{
			vis[i]=1;
			dfs(u+1,mer(s,str[i]));
			vis[i]=0;	
		}	
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>str[i];
	dfs(0,"");
	cout<<ans<<endl;
}
