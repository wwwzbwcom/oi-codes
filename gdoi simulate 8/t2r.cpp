#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
int n,d;
int ans=0;
string str[1000];
int main()
{
//	freopen("in.txt","w",stdout);
	srand(time(NULL));
	cout<<25<<endl;
	for(int i=0;i<1000;i++)
	{
		cout<<rand()%1000<<" "<<rand()%1000<<" "<<rand()%1000<<endl; 
	}
}
