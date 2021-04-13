#include<iostream>
using namespace std;
int main()
{
	int w,h,a;
	cin>>w>>h>>a;
	if(a==180)	cout<<w*h<<endl;
	else	cout<<min(w,h)*min(w,h)<<endl; 
}
