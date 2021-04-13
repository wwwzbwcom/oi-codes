#include<iostream>
#include<string>
using namespace std;
int n,d;
int ans=0;
string str[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	cin>>n>>d;
	for(int i=0;i<n;i++)	cin>>str[i];
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			int dif=0;
			for(int k=0;k<4;k++)	if(str[i][k]!=str[j][k])	dif++;
		//	cout<<i<<" "<<j<<" "<<dif<<endl;
			if(dif==d)	ans++;
		}
	cout<<ans<<endl;
}
