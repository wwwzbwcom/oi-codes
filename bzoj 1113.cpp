#include<iostream>
#include<stack>
using namespace std;
int n;
stack <int> sta;
int ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int t,uh;	cin>>t>>uh;
		while(!sta.empty())
		{
			int vh=sta.top();
			if(vh<uh)	break;
			else
			{
				sta.pop();
				if(uh==vh)	break;
				else	ans++;
			}
		}
		sta.push(uh);
	}
	while(!sta.empty())	sta.pop(),ans++;
	cout<<ans<<endl;
}
