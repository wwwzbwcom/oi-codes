#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	cout<<10<<endl;
	srand(time(NULL));
	for(int i=0;i<10;i++)
	{
		int len=rand()%100+500;
		for(int i=0;i<len;i++)
		{
			int tmp=rand()%4;
			if(tmp==0)	cout<<'A';
			if(tmp==1)	cout<<'C';
			if(tmp==2)	cout<<'T';
			if(tmp==3)	cout<<'G';
		}
		cout<<endl;
	}
}
