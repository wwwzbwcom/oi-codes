#include<iostream>
#include<cmath> 
using namespace std;
int main()
{
	int n;
	int s[10000];
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>s[i];
	sort(s+1,s+n+1);
	if(n==1)
	{
		cout<<s[1];
		cout<<s[1];
	}
	else
	{
		int nt=n,ans=0;
		while(n>3)
		{
			int a=s[nt]+s[1]+s[nt-1]+s[1];
			int b=s[2]+s[1]+s[nt]+s[2];
			ans+=min(a,b);
			nt-=2;
		}
		if(nt==2)	ans+=s[2];
		else if(nt==3)	ans+=s[nt]+s[nt-1]+s[1];
		
		cout<<ans<<endl;
		
		nt=n;
		while(n>3)
		{
			int a=s[nt]+s[1]+s[nt-1]+s[1];
			int b=s[2]+s[1]+s[nt]+s[2];
			if(a<b)
			{
				cout<<s[nt]<<" "<<s[1]<<endl;
				cout<<s[1]<<endl;
				cout<<s[nt-2]<<" "<<s[1]<<endl;
				cout<<s[1]<<endl;
			}
			else
			{
				cout<<s[1]<<" "<<s[2]<<endl;
				cout<<s[1]<<endl;
				cout<<s[nt-1]<<" "<<s[nt-2]<<endl;
				cout<<s[2]<<endl;
			}
			nt-=2;
		}
		if(nt==2)	cout<<s[1]<<" "<<s[2]<<endl;
		else if(nt==3)
		{
			cout<<s[1]<<" "<<s[nt-1]<<endl;
			cout<<s[1]<<" "<<endl;
			cout<<s[1]<<" "<<s[nt]<<endl;
		}
	}
	
}
