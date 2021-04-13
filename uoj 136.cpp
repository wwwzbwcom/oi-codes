#include<iostream>
using namespace std;
int main()
{
	int gn;	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		int n,m;	cin>>n>>m;	n--;	m--;
		
		int ans1=0,ans2=0;
		
		if(n<=2)	ans1+=n;
		else		ans1+=2+(n-2)/2+(n%2);
		if(m<=2)	ans1+=m;
		else		ans1+=2+(m-2)/2+(m%2);
		
		if(n<=1&&m<=1)	ans2=2;
		else
		{
			int t=min(n,m);
			ans2=2+(t-1);
		//	cout<<ans2<<endl; 
			n-=t;	m-=t;
			if(n<=m)	swap(n,m);
		//	cout<<n<<endl; 
			if(n<=2)	ans2+=n;
			else		ans2+=1+(n-1)/2+((n-1)%2);
		}
		
		cout<<min(ans1,ans2)<<endl;
	}
}
