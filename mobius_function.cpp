#include<iostream>
using namespace std;
const int n=1e7;
bool boo[n+100];
int pri[n+100],pn=0;
int mob[n+100];
int main()
{
	boo[1]=1;
	mob[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(boo[i]==0)	pri[pn++]=i,mob[i]=-1;
		for(int j=0;j<pn;j++)
		{
			if(i*pri[j]>n)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				mob[i*pri[j]]=0;
				break;
			}
			else	mob[i*pri[j]]=-mob[i];
		}
	}
	for(int i=1;i<=100;i++)	cout<<i<<" "<<mob[i]<<endl; 
}
