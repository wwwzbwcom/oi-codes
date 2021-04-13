#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	freopen("graph.in","w",stdout);
	srand(time(0));
	for(int g=1;g<=1;g++)
	{
		int n=10000,m=100000;
		cout<<n<<" "<<m<<endl;
		for(int i=1;i<=n-1;i++)	cout<<i<<" "<<i+1<<" "<<rand()+rand()<<endl;
		for(int i=1;i<=m-(n-1);i++)
		{
			printf("%d %d %d\n",rand()%n,rand()%n,rand());
			
		}
	}
	cout<<0<<" "<<0<<endl;
}
