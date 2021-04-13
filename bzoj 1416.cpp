#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20100;
int t,n,d;
int sum;
int a[maxn];
int x[maxn],y[maxn];
int cnt1[maxn],cnt2[maxn];
int boo[maxn],pri[maxn],pn;
int idx[maxn];
void init()
{
	boo[1]=1;
	for(int i=2;i<=maxn;i++)
	{
		if(boo[i]==0)	pn++,pri[pn]=i,idx[i]=pn;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
struct BIGNUM
{
	int s[10000],l;
	BIGNUM()
	{
		memset(s,0,sizeof s);	l=0;
	}
	BIGNUM(int val)
	{
		memset(s,0,sizeof s);	l=0;
		while(val)
		{
			s[l++]=val%10000;
			val/=10000;
		}
	}
	BIGNUM operator *(const int &in)const
	{
		BIGNUM ans=*this;
		int carry=0;
		for(int i=0;i<l;i++)
		{
			ans.s[i]=s[i]*in+carry;
			carry=ans.s[i]/10000;
			ans.s[i]%=10000;
		}
		while(carry)
		{
			ans.s[ans.l++]=carry%10000;
			carry/=10000;
		}
		return ans;
	}
	void output()
	{
		printf("%d",s[l-1]);
		for(int i=l-2;i>=0;i--)	printf("%0.4d",s[i]);
	}
}v1(1),v2(1);
void calc(int in,int vec[])
{
	for(int i=1;i<=pn&&in>=pri[i];i++)	while(in%pri[i]==0)	vec[i]++,in/=pri[i];
}
int main()
{
	init();
	scanf("%d%d%d",&t,&n,&d);
	for(int i=1;i<=t;i++)	scanf("%d",&a[i]),sum+=a[i];
	for(int i=1;i<=n;i++)	scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
	{
		calc(a[y[i]],cnt1);	calc(sum,cnt2);
		a[y[i]]+=d;		sum+=d;
	}
	for(int i=1;i<=pn;i++)
	{
		if(cnt1[i]>cnt2[i])	cnt1[i]-=cnt2[i],cnt2[i]=0;
		else				cnt2[i]-=cnt1[i],cnt1[i]=0;
	}
	for(int i=1;i<=pn;i++)
	{
		for(int j=1;j<=cnt1[i];j++)	v1=v1*pri[i];
		for(int j=1;j<=cnt2[i];j++)	v2=v2*pri[i];
	}
	
	v1.output();
	printf("/");
	v2.output();
}
