#include<iostream>
#include<string>
#include<cstdio>
#include<stack>
#include<cmath>
using namespace std;
string str;
stack <double> sta;
double n1=0,n2=0;
double s2d(int s)
{
	double ans=0;
	double mul;
	
	int e=s;
	while(e>=0&&'0'<=str[e]&&str[e]<='9')	e--;
	if(str[e]=='.')
	{
		mul=0.1;
		for(int i=e+1;i<=s;i++)
		{
			ans+=mul*(double)(str[i]-'0');
			mul/=10;
		}
		
		s=e-1,e=s;
		while(e<str.size()&&'0'<=str[e]&&str[e]<='9')	e--;
		
		mul=1;
		for(int i=s;i>e;i--)
		{
			ans+=mul*(double)(str[i]-'0');
			mul*=10;
		}	
	}
	else
	{
		mul=1;
		for(int i=s;i>e;i--)
		{
			ans+=mul*(double)(str[i]-'0');
			mul*=10;
		}
	}
	return ans;
}
int main()
{
//	str="11.11";
//	cout<<s2d(4)<<endl;
//	return 0;
	getline(cin,str);
	for(int i=str.size()-1;i>=0;i--)
	{
		if(str[i]==' ')	continue;
		else if('0'<=str[i]&&str[i]<='9')
		{
			sta.push(s2d(i));
		//	cout<<s2d(i)<<endl;
			while(('0'<=str[i]&&str[i]<='9')||str[i]=='.')	i--;
		}
		else
		{
			n1=sta.top();sta.pop();
			n2=sta.top();sta.pop();
		//	cout<<n1<<" "<<n2<<" "<<str[i]<<endl;
			if(str[i]=='+')	sta.push(n1+n2);
			if(str[i]=='-')	sta.push(n1-n2);
			if(str[i]=='*')	sta.push(n1*n2);
			if(str[i]=='/')	sta.push(n1/n2);
		}
	}
	printf("%f\n",sta.top());
}
