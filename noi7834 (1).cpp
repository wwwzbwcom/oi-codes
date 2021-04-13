#include<iostream>
using namespace std;
int group[20][20];
int cnt[20];
int s[20];
int gn=0;
int n;
int gcd(int a,int b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>s[i];
	for(int i=1;i<=n;i++)
	{
		int flag1=0;
		for(int j=0;j<gn;j++)
		{
			int flag2=0;
			for(int k=0;k<cnt[j];k++)
				if(gcd(group[j][k],s[i])!=1)
				{
					flag2=1;
					break;
				}
			if(flag2==0)
			{
				group[j][cnt[j]++]=s[i];
				flag1=1;
				break;
			}
		}
		if(flag1==0)	group[gn][cnt[gn]++]=s[i],gn++;
	}
	cout<<gn<<endl;
}
