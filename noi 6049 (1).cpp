#include<iostream>
using namespace std;
const int maxn=2000;
int n;
int dyp[maxn];
int main()
{
	cin>>n;
	if(n==0)
	{
		cout<<0<<endl;
		return 0;
	}
	dyp[0]=1;
	for(int i=0;i<=1000;i++)	dyp[i+10]+=dyp[i];
	for(int i=0;i<=1000;i++)	dyp[i+20]+=dyp[i];
	for(int i=0;i<=1000;i++)	dyp[i+50]+=dyp[i];
	for(int i=0;i<=1000;i++)	dyp[i+100]+=dyp[i];
	cout<<dyp[n];
}
