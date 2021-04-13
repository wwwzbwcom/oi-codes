#include<iostream>
#include<cstdio>
using namespace std;
int sg(int a,int b)
{
	long long cur=1;
	for(int i=0;i<=30;i++,cur*=2)	if((a-1)%(cur*2)<cur&&(b-1)%(cur*2)<cur)	return i;
}
int gn,n;
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n;
		int ans=0;
		for(int i=1;i<=n/2;i++)
		{
			int a,b;	scanf("%d%d",&a,&b);
			ans=ans^sg(a,b);
		}
		if(ans)	cout<<"YES"<<endl;
		else	cout<<"NO"<<endl;
	}
}
