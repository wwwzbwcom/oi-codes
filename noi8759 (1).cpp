#include<iostream>
using namespace std;
int up[100];
int down[100];
int now[100];
int main()
{
	int a,n,m,x;
	cin>>a>>n>>m>>x;
	for(int i=0;i<=a;i++)
	{
		up[1]=a;down[1]=0;now[1]=a;
		up[2]=i;down[2]=i;now[2]=a;
		for(int j=3;j<n;j++)
		{ 
			up[j]=up[j-1]+up[j-2];
			down[j]=up[j-1];
			now[j]=now[j-1]+up[j]-down[j];
		}
		if(now[n-1]==m)
		{
			cout<<now[x]<<endl;
		}
	}
}
