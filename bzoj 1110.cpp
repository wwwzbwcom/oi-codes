#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int con[100100];
int wei[100100];
int kin[100100];
int num[100100];
int n,m;
int kn;
int cur=0;
int ans=0;
void lend(int cur)
{
	if(cur==kn)	return;
	if(num[cur]==0)
	{
		lend(cur+1);
		if(num[cur+1]>0)
		{
			num[cur+1]--;
			num[cur]+=kin[cur+1]/kin[cur];
		}
	}
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)	scanf("%d",&con[i]);
    for(int i=0;i<m;i++)	scanf("%d",&wei[i]);
    
	sort(wei,wei+m);
	for(int i=0;i<m;i++)	kin[i]=wei[i];
	kn=unique(kin,kin+m)-kin;
	
	for(int i=0;i<n;i++)
	{
		int tmp=con[i];
		for(int j=kn-1;j>=0;j--)
		{
			num[j]+=tmp/kin[j];
			tmp=tmp%kin[j];
		}
	}
	
	//for(int i=0;i<kn;i++)	cout<<kin[i]<<" "<<num[i]<<endl;
	
	int cur=0;
	for(int i=0;i<m;i++)
	{
		if(wei[i]>kin[cur])	cur++;
		if(num[cur]==0)	lend(cur);
	//	cout<<cur<<" "<<num[cur]<<endl;
		if(num[cur]>0)	num[cur]--,ans++;
		else	break;
		
	//	for(int i=0;i<kn;i++)	cout<<kin[i]<<" "<<num[i]<<endl;
	}
	
	printf("%d",ans);
}
