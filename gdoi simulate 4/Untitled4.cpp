#include<iostream>
using namespace std;
int a[10000];
int b[10000];
int main()
{
	a[1]=1;	b[1]=2;
//	swap(a,b);
//	cout<<a[0]<<" "<<b[0]<<endl;
	int *p1=a,*p2=b;
	swap(p1,p2);
	((int*)b)=p1,a=p2;
	cout<<a[1]<<" "<<b[1]<<endl;
}
