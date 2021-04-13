#include<iostream>
using namespace std;
int main()
{
	int gn;
	cin>>gn;
	double bad,good;
	while(gn--)
	{
		cin>>bad>>good;
		int cnt=0;
		while(bad>1e-6)
		{
			bad-=good;
			good*=1.05;
			bad*=2;
			if(bad>=100000)	bad=100000;
			cnt++;
		}
		cout<<cnt<<endl;
	}
}
