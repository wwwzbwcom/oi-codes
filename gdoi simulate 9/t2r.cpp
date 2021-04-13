#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	int n=10000;
	srand(time(NULL));
	cout<<n<<" "<<n<<endl;
	for(int i=0;i<n;i++)
	{
		int t=rand()%6;
		if(t%2==0)	cout<<'R'<<" "<<rand()%n<<" "<<rand()%n<<endl;
		else
		{
			if(t%3==0)	cout<<'K'<<" "<<rand()%10000<<endl;	
			else	cout<<'T'<<" "<<rand()%n<<" "<<rand()%n<<" "<<rand()%n<<endl;
		}
	}
}
