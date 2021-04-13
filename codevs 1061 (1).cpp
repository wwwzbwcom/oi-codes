#include<iostream>
#include<cstring>
using namespace std;
string s,a;
int main()
{
	cin>>s;
	for(int i=0;i<s.size();i+=2)
	{
		char cur;
		if(s[i]=='L')	cur='A';
		else cur='A'+10;
		cur+=s[i+1]-'0';
		a+=cur;
	}
//	cout<<a<<endl;
	int ans=0,p=0;
//	cout<<a.size()<<endl;
	for(int i=1;i<a.size();i++)
		for(int j=0;j+2*i-1<a.size();j++) 
		{
		//	cout<<j<<"="<<i<<" "<<j+i<<"="<<i<<endl;
			if(a.substr(j,i)==a.substr(j+i,i))
			{
				ans=i,p=j;
				break;
			}
		}
//	cout<<p*2<<" "<<2*ans<<endl;
	if(ans)	cout<<s.substr(p*2,2*ans);
	else cout<<"NO"<<endl; 
}
