#include<iostream>
using namespace std;
const int n=1e8;
bool boo[n+100];
int pri[n+100],pn=0;
int main()
{
	for(int i=2;i<=n;i++)
	{
		if(boo[i]==false)	pri[pn++]=i;
		for(int j=0;j<pn;j++)
		{
			if(i*pri[j]>n)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
	cout<<pn<<endl;
}
