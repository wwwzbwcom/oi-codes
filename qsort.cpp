#include<iostream>
#include<cstring>
using namespace std;
int sto[]={5,3,4,1,2};
int tmp[1000000],tn;
void mergesort(int le,int re)
{
	if(le==re)	return;
	else
	{
		
		int mid=(le+re)/2;
		mergesort(le,mid),	mergesort(mid+1,re);
		int lp=le,rp=mid+1;	tn=0;
		while(lp<=mid&&rp<=re)
		{
			if(sto[lp]<sto[rp])	tmp[tn++]=sto[lp],lp++;
			else	tmp[tn++]=sto[rp],rp++;
		}
		while(lp<=mid)	tmp[tn++]=sto[lp],lp++;
		while(rp<=re)	tmp[tn++]=sto[rp],rp++;
		memcpy(sto+le,tmp,sizeof(int)*tn);	
	}
}
int main()
{
	mergesort(0,4);
	for(int i=0;i<=4;i++)	cout<<sto[i]<<" ";
}
