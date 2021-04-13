#include<iostream>
using namespace std;
int gn,n;
int ans=0;
int main()
{
	cin>>gn;
	while(gn--)
	{
		ans=0;
		cin>>n;
		for(int a1=0;a1<=n;a1++)
			for(int a2=0;a2<=n;a2++)
				for(int a3=0;a3<=n;a3++)
					if((a1+a2)%2==0&&(a2+a3)%3==0&&(a1+a2+a3)%5==0)
						ans=max(ans,a1+a2+a3);
		cout<<ans<<endl;
	}
}
