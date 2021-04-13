#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=100000;
int gn,n,m,p;
int boo[maxn];
int pri[maxn],pn;
int mob[maxn];
int eul[maxn];
int cnt[maxn];
int sum,ans;
void mobius()
{
	boo[1]=1;	mob[1]=1;	eul[1]=0;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[pn++]=i,mob[i]=-1,eul[i]=1;
		for(int j=0;j<pn;j++)
		{
			if(pri[j]*i>=maxn)	break;
			boo[pri[j]*i]=1;
			eul[pri[j]*i]=eul[i]+1;
			if(i%pri[j]==0)
			{
				mob[pri[j]*i]=0;
				break;
			}
			else	mob[pri[j]*i]=-mob[i];
		}
	}
	for(int i=1;i<maxn;i++)	mob[i]+=mob[i-1];
}
int gcd(int a,int b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
int getnum(int a)
{
	int ans=0;
//	cout<<a<<endl;
	for(int i=0;pri[i]<=a;i++)
	{
	//	cout<<a<<" "<<pri[i]<<endl;
		while(a%pri[i]==0)	a/=pri[i],ans++;
	}
	return ans;
}
int main()
{
	mobius();
//	cout<<getnum(6)<<endl;
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n>>m>>p;
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(getnum(gcd(i,j))<=p)	ans++;
		cout<<ans<<endl;
	}
}
