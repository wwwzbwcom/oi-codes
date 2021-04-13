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
	cout<<1000<<" "<<rand()%4<<endl;
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<4;j++)
		{
			int t=rand()%36;
			if(t<=9)	cout<<t;
			else
			{
				char c=t+'a'-10;
				cout<<c;
			}
		}
		cout<<endl;
	}
}
