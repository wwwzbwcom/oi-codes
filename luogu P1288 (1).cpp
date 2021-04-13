#include<iostream>
using namespace std;
int n;
int s[100];
int cnt1=0,cnt2=0;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>s[i];
	for(int i=0;i<n;i++)	if(s[i])	cnt1++;	else	break;
	for(int i=n-1;i>=0;i--)	if(s[i])	cnt2++;	else	break;
	//cout<<cnt1<<" "<<cnt2<<endl;
	if(cnt1%2||cnt2%2)	cout<<"YES"<<endl;
	else	cout<<"NO"<<endl;
}
