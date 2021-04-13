#include "worldline.h"
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn=20000;
int idx[maxn];
int query_permutation(int n,int ans[])
{
	new_round();
	
	int mid=n/2,lim=n;
	if(n%2==0)	mid--,lim--;
	
	for(int i=1;i<mid;i++)		addedge(i,i+1);
	for(int i=mid+1;i<lim;i++)	addedge(i,i+1);
	
	int cnt[2];
	next_step();
	memset(idx,-1,sizeof idx);
	idx[1]=0;
	for(int i=2;i<=n;i++)
		if(query(i-1,i))	idx[i]=idx[i-1]^1,cnt[idx[i]]++;
		else				idx[i]=idx[i-1]	 ,cnt[idx[i]]++;
	if(cnt[0]==cnt[1])
	{
		idx[1]=1;
		for(int i=2;i<=n;i++)
			if(query(i-1,i))	idx[i]=idx[i-1]^1,cnt[idx[i]]++;
			else				idx[i]=idx[i-1]	 ,cnt[idx[i]]++;
	}
	if(n%2==0)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)	if(idx[j]==idx[i])
			{
				if(query(i,j)==0)	cnt++;	else	break;
				if(cnt>2)
				{
					cnt[idx[i]]--;
					idx[i]=-1;
					break;
				}
			}
			if(idx[i]==-1)	break;
		}
	}
	
	new_round();
	for(int i=1;i<=mid;i++)		addedge(i,mid+i);
	next_stage();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(query(i,j))
			{
				if(cnt[0]<cnt[1])
				{
					
				}
				else				
			}
	
}
