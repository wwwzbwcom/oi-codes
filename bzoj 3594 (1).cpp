#include<cstdio>
//#include<iostream>
#include<algorithm>
using namespace std;
int n,k;
int hei[10100];
int dyp[10100][600];
int ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)	scanf("%d",&hei[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			for(int p=0;p<=k;p++)
			{ 
				if(hei[j]<=hei[i])	dyp[i][p]=max(dyp[i][p],dyp[j][p]+1);
				else	if(p+hei[j]-hei[i]<=k)	dyp[i][p+hei[j]-hei[i]]=max(dyp[i][p+hei[j]-hei[i]],dyp[j][p]+1);
			} 
	for(int i=1;i<=n;i++)
	{
		for(int p=0;p<=k;p++)	ans=max(dyp[i][p],ans);
	}
	printf("%d",ans+1);
}
