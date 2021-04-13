#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=100100;
struct Node
{
	int c,p;
	bool operator<(const Node &in)const
	{
		if(p-c==in.p-in.c)	return c<in.c;
		else	return p-c<in.p-in.c;
	}
}s[maxn];
int k,n;
int mni[maxn];
int cur=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&s[i].c),s[i].p=i;
	sort(s+1,s+n+1);
	
	for(int i=1;i<=n;i++)
		if(s[i].p-s[i].c>=0)
		{
			int t=lower_bound(mni,mni+cur,s[i].c)-mni;
			if(t==cur)	cur++;
			mni[t]=s[i].c;
		}
	printf("%d\n",cur);
}
