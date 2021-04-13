#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int x1,x2;
int main()
{
	srand(time(0));
	x1=rand()%100;	x2=rand()%100;
	cout<<"x2";
	if(x1+x2>=0)	cout<<"+";	else	cout<<"-";
	cout<<x1+x2<<"x";
	if(x1*x2>=0)	cout<<"+";	else	cout<<"-";
	cout<<x1*x2<<"=0"<<endl; 
}
