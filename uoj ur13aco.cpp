#include<cstdio>
#include<cstring>
//#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+100;
int n,q;
int sto[maxn];
char str[maxn];
int tmp[maxn],tn=0;
int pos[maxn];
int idx[maxn];
int boo[maxn];
int work()
{
	tn=0;
	memset(boo,0,sizeof boo);
	memset(pos,-1,sizeof pos);
	for(int i=1;i<=n;i++)
	{
		if(str[i-1]=='1')	tmp[++tn]=sto[i];
		else	idx[i]=tn,pos[sto[i]]=i;
	}
	int ans=1e9;
	for(int i=n;i>=1;i--)
		if(pos[i]!=-1)
		{
			int pl=idx[pos[i]],pr=idx[pos[i]]+1,cur=0,flag=0;
			while(pl>=1&&tmp[pl]>sto[pos[i]])
			{
				if(boo[pl])	{flag=1;break;}
				boo[pl]=1;	pl--;	cur++;
			}
			if(flag)	continue;
			while(pr<=tn&&tmp[pr]>sto[pos[i]])
			{
				if(boo[pr])	{flag=1;break;}
				boo[pr]=1;	pr++;	cur++;
			}
			if(flag)	continue;
			ans=min(ans,cur+1);
		}
	return ans;
}
int main()
{
//	freopen("ex_A4.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&sto[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%s",str);
		printf("%d\n",work());
	}
}
