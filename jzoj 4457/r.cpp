#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
long long l,mul;
int main()
{
	srand(time(NULL));
	mul=1;
	for(int i=1;i<=11;i++)	l+=(rand()%10)*mul,mul*=10;
	cout<<l<<" "<<l+rand()*rand()<<endl; 
}
