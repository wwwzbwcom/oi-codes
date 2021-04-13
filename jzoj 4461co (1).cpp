#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=200000;
int n;
int hei[maxn];
int ans[maxn];
void workl(int le,int re,int la,int ra)
{
	if(le>re)	return;
	int me=(le+re)>>1;
	int tans=0,lp=0,rp=0;
	for(int i=la;i<=min(me,ra);i++)
	{
		int tmp=hei[i]+(int)ceil(sqrt(abs(me-i)))-hei[me];
		if(tmp>tans)
		{
			tans=tmp;
			lp=rp=i;
		}
		else	if(tmp==tans)	rp=i;
	}
//	cout<<lp<<" "<<rp<<endl;
	ans[me]=max(ans[me],tans);
	if(le!=re)
	{
		workl(le,me-1,la,rp);
		workl(me+1,re,lp,ra);
	}
}
void workr(int le,int re,int la,int ra)
{
	if(le>re)	return;
	int me=(le+re)>>1;
	int tans=0,lp=0,rp=0;
	for(int i=max(la,me);i<=ra;i++)
	{
		int tmp=hei[i]+(int)ceil(sqrt(abs(me-i)))-hei[me];
		if(tmp>tans)
		{
			tans=tmp;
			lp=rp=i;
		}
		else	if(tmp==tans)	rp=i;
	}
//	cout<<lp<<" "<<rp<<endl;
	ans[me]=max(ans[me],tans);
	if(le!=re)
	{
		workr(le,me-1,la,rp);
		workr(me+1,re,lp,ra);
	}
}
int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&hei[i]);
	workl(1,n,1,n);
	workr(1,n,1,n);
	for(int i=1;i<=n;i++)	printf("%d\n",ans[i]);
}
