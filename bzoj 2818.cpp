#include<iostream>
using namespace std;
const int maxn=100000;
int boo[maxn+100];
int pri[maxn+100],pn;
int mob[maxn+100];
int n,ans;
void init()
{
	boo[1]=1;mob[1]=1;
	for(int i=2;i<=maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i,mob[i]=-1;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				mob[i*pri[j]]=0;
				break;
			}
			else	mob[i*pri[j]]=-mob[i];
		}
	}
}
int main()
{
	cin>>n;	n--;
	init();
	for(int i=1;i<=n;i++)	ans+=mob[i]*(n/i)*(n/i);//cout<<mob[i]<<" "<<(n/i)*(n/i)<<endl;
	cout<<ans+2<<endl;
}
