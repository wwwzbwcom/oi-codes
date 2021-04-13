#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int gn;
	cin>>gn;
	while(gn--)
	{
		int tol,n,cur;
		cin>>tol>>n;
		int min0=0,max0=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&cur);
			min0=max(min0,min(cur,tol-cur));
			max0=max(max0,max(cur,tol-cur));
		}
		cout<<min0<<" "<<max0<<endl;
	}
}
