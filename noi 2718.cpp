#include<iostream>
using namespace std;
int c[50][50];
int n,m;
void init()
{
	c[0][0]=1;
	for(int i=1;i<50;i++)
	{
		c[i][0]=1;
		for(int j=1;j<50;j++)	c[i][j]=c[i-1][j]+c[i-1][j-1]; 
	} 
}
int main()
{
	init();
	cin>>n>>m;
	cout<<c[n+m-2][m-1]<<endl;
}
