#include<iostream>
#include<cstring>
#include<map>
using namespace std;
const int maxn=1e5+10;
const int mod=1e8+7;
int main()
{
	for(int i=1;i<=mod;i++)
		if((i*130ll)%(long long)mod==1)	cout<<i<<endl;
}
