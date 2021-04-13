#include<iostream>
#include<cstdio>
using namespace std;
int n;
int dyp[10100][4][2];
int sto[10100];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	dyp[0][0][0]=1;
	dyp[0][1][0]=1;
	for(int i=0;i<n;i++)
	{
		if(sto[i+1]>=0)		dyp[i+1][sto[i+1]  ][0]+=dyp[i][0][0];
		if(sto[i+1]-1>=0)	dyp[i+1][sto[i+1]-1][0]+=dyp[i][0][1];
		if(sto[i+1]-1>=0)	dyp[i+1][sto[i+1]-1][1]+=dyp[i][1][0];
		if(sto[i+1]-2>=0)	dyp[i+1][sto[i+1]-2][1]+=dyp[i][1][1];
	}
	printf("%d\n",dyp[n][0][0]+dyp[n][0][1]);
}
