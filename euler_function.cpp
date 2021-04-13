#include<iostream>
using namespace std;
const int n=1e7;
bool boo[n+100];
int	pri[n+100],pn;
int eul[n+100];
int main()
{
	boo[1]=1;
	eul[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(boo[i]==0)	pri[pn++]=i,eul[i]=i-1;
		for(int j=0;j<pn;j++)
		{
			if(i*pri[j]>n)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				eul[i*pri[j]]=eul[i]*pri[j];
				break;
			}
			else	eul[i*pri[j]]=eul[i]*(pri[j]-1);
		}
	}
}
