#include<iostream>
using namespace std;
int main()
{
	int n;
	while(cin>>n,n)
	{
		int	tmp=n;
		int	cnt=0;
		while(n)
		{
			cnt+=n%2;
			n/=2;
		}
		n=tmp;
		for(int i=n+1;i<=2*n;i++)
		{
			int cc=0;
			int cur=i;
			while(cur)
			{
				cc+=cur%2;
				cur/=2;
			}
			if(cc==cnt)
			{
				cout<<i<<endl;
				break;
			}
		}
	}
}
