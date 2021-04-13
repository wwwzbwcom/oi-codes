#include<iostream>
#include<cstring> 
#include<string>
using namespace std;
string str;
string tmp;
int boo[50100];
int main()
{
	cin>>str;
	for(int i=1;i<=str.size()/2;i++)
	{
		memset(boo,0,sizeof boo);
		for(int j=0;j+2*i<=str.size();)
		{
			if(str.substr(j,i)==str.substr(j+i,i))	boo[j]^=1,boo[j+i]^=1,j=j+i;
			else	j++;
		}
		int con=0;
		tmp="";
		for(int j=0;j<str.size();j++)
		{
			if(boo[j]==1)	con^=1;
		//	cout<<j<<" "<<str[j]<<" "<<boo[j]<<" "<<con<<endl;
			if(con==0)	tmp+=str[j];
		}
		str=tmp;
		//cout<<str<<endl;
		//getchar();
	}
	cout<<str;
}
