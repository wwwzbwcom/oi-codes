#include<cstdio>
//#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1000100;
int n;
int dis[maxn];
int num[maxn];
int fee[maxn];
int sum[maxn];
int x[maxn],y[maxn];
int l,r;
int dyp[maxn][2];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d%d%d",&dis[i],&num[i],&fee[i]);
	for(int i=1;i<=n;i++)	dis[i]=dis[n]-dis[i];
	for(int i=1;i<=n;i++)	sum[i]=dis[i]*num[i];
	for(int i=n;i>=1;i--)	sum[i]+=sum[i+1];
//	for(int i=n;i>=1;i--)	printf("%d %d %d\n",i,sum[i],dis[i]);
	for(int i=n;i>=1;i--)
	{
		dyp[i][1]=min(dyp[i+1][0],dyp[i+1][1])+fee[i];
		while(l+1<r&&x[l]+y[l]>x[l+1]+y[l+1])	l++;
		if(i==n)	dyp[i][0]=1e9;
		else	dyp[i][0]=x[l]+y[l]+sum[i];
		int xt=dyp[i][1],yt=-sum[i];
		while(l+1<r&&(yt-y[l-1])*(xt-x[l-1])>(y[l-1]-y[l-2])*(x[l-1]-x[l-2]))	r--;
		x[r]=xt;	y[r]=yt;	r++;
	}
//	for(int i=n;i>=1;i--)	printf("%d %d\n",dyp[i][0],dyp[i][1]);
	printf("%d\n",min(dyp[1][0],dyp[1][1]));
} 
