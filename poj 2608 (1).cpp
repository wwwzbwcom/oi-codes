#include<iostream>
#include<string>
using namespace std;
string f="BFPVCGJKQSXZDTLMNRAEIOUHWY";
string t="11112222222233455600000000";
string s;
int main()
{
	while(cin>>s)
	{
		char l=0;
		for(int i=0;i<s.size();i++)
			for(int j=0;j<f.size();j++)
				if(s[i]==f[j])
				{
					if(t[j]!=l&&t[j]!='0')cout<<t[j];
					l=t[j];
				}
		cout<<endl;
	}
}
