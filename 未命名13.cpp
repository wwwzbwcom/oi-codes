#include<ext/rope>
#include<iostream>
#include<vector>
using namespace __gnu_cxx;
using namespace std;
rope <int> rop;
int main()
{
	int p[]={1,2,3};
	rop.insert(0,p,3);
	for(int i=0;i<3;i++)	cout<<i<<"="<<rop[i]<<endl; 
//	cout<<val<<" "<<rop.size()<<endl;
//	for(int i=0;i<10;i++)	cout<<rop.substr(0,1)<<" ";
}
