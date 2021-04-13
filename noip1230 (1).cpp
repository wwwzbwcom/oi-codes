#include<iostream>
#include<map>
using namespace std;
map <int,int> book;
int main()
{
	int n,m,t;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		book[t]=1;
	}
	for(int j=0;j<m;j++)
	{
		cin>>t;
		if(book[t]==1)	cout<<"YES"<<endl;
		else	cout<<"NO"<<endl,book.erase(t);
	}
} 
