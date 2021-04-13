#include<iostream>
using namespace std;
const int maxn=1001;
int val[maxn];
int n;
int mxa=-1,mni=1001;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>val[i];
	for(int i=1;i<=n;i++)	mxa=max(mxa,val[i]),mni=min(mni,val[i]);
	cout<<mxa-mni<<endl;
 } 
