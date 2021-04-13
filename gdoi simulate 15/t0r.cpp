#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	int n=100;
	srand(time(0));
	cout<<n<<endl;
	for(int i=1;i<=n;i++)	cout<<rand()%1000-500<<" ";
	cout<<endl;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
	{
		int cmd=rand()%2;	cout<<cmd<<" ";
		if(cmd==0)	cout<<rand()%n+1<<" "<<rand()%1000-500<<endl;
		if(cmd==1)
		{
			int l=rand()%n+1,r=rand()%n+1;	if(l>r)	swap(l,r);
			cout<<l<<" "<<r<<" "<<rand()%21<<endl;
		}
	}
	
}
