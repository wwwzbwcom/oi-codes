#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
bool cmp(string a,string b)
{
	if(a.size()<b.size())	return 1;
	else if(a.size()>b.size())	return 0;
	else if(a.size()==b.size())
	{
		int cnt=0;
		while(a[cnt]==b[cnt]&&cnt<a.size())
		{
			if(a[cnt]>b[cnt])	return 1;
			if(a[cnt]<b[cnt])	return 0;
			cnt++;
		}
	}
}
struct Store
{
	string s[200];
	int cnt;
}ss[13][32];
int main()
{
	int n;
	while(cin>>n)
	{
//		cin>>n;
		for(int i=1;i<=12;i++)
			for(int j=1;j<=31;j++)
				ss[i][j].cnt=0;
		
		for(int i=0;i<n;i++)
		{
			string s;
			int m,d;
			cin>>s>>m>>d;
			ss[m][d].s[ss[m][d].cnt++]=s;
		}
		
		int flag=0;
		for(int i=1;i<=12;i++)
			for(int j=1;j<=31;j++)
				if(ss[i][j].cnt>1)
				{
					cout<<i<<" "<<j<<" ";
					sort(ss[i][j].s,ss[i][j].s+ss[i][j].cnt,cmp);
					for(int k=0;k<ss[i][j].cnt;k++)	cout<<ss[i][j].s[k]<<" ";
					cout<<endl;
					flag=1;
				}
		if(flag==0)	cout<<"None"<<endl;
	}
}
