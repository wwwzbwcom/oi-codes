#include<iostream>
#include<cstring>
using namespace std;
char s[1000];
char a;
int book[100];
int sign[100];
int main()
{
	cin>>s;
	int qf=1;
	int nf=1;
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		if(s[i]=='+') nf=1;
		else if(s[i]=='-') nf=-1;
		else if(s[i]=='=') qf=-1,nf=1;
		else
		{
			book[s[i]-'A']=1;
			sign[s[i]-'A']=nf*qf;
		}
	}
	cin>>a;
	for(int i=0;i<26;i++)
		if(i!=a-'A'&&book[i]==1)
		{
			if(sign[i]*sign[a-'A']==1) cout<<"-";
			else cout<<"+";
			char t=i+'A'; 
			cout<<t;
		}
}
