#include<iostream>
using namespace std;
int main()
{
	int n;	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int val,cnt=0,tmp;
		cin>>val;
		tmp=val;
		while(tmp)
		{
			if(tmp%2)	cnt++;
			tmp/=2;
		}
		cout<<val-cnt<<endl; 
	}
}
