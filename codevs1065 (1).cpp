#include<iostream>
using namespace std;
int ans=0;
int n;
void dfs(int bit,int last,int times)
{
//	cout<<bit<<" "<<last<<" "<<times<<endl;
	if(bit==n)
	{
		ans++;
		return;
	}
	if(times<2)	dfs(bit+1,last,times+1),dfs(bit+1,last^1,1);
	else	dfs(bit+1,last^1,1);
}
int main()
{
	cin>>n;
	dfs(0,0,0);
	if(n!=0)	cout<<ans<<endl; 
	else	cout<<0<<endl;
}
