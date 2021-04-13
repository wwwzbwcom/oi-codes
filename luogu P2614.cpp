#include<iostream>
#include<string>
using namespace std;
string s;
int n,T;
int main()
{
	cin>>n>>T;
	getchar();
	double ans=0;
	for(int i=0;i<n;i++)
	{
		getline(cin,s);
		int len=s.size();
		int lev=1;
		for(int j=0;j<len;j++)
		{
			if(s[j]==' ')	continue;
			if(s[j]=='('){	lev*=2;	continue;	}
			if(s[j]==')'){	lev/=2;	continue;	}
			double cur=1;
			for(int	k=j+1;k<len;k++)
			{
				if(s[k]!='-'&&s[k]!='.')	break;
				if(s[k]=='-')	cur++;
				if(s[k]=='.')	cur*=1.5;
				j=k;
			}
			ans+=cur/(double)lev;
		}
	}
	cout<<(int)(ans*(60.0/(double)T))<<endl;
}
