#include<iostream>
using namespace std;
const int maxn=100100;
int n,m;
int ans;
int boo[maxn];
int pri[maxn],pn;
int mul[maxn];
void init()
{
	boo[1]=1;	mul[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i,mul[i]=-1;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				mul[i*pri[j]]=0;
				break; 
			}
			else	mul[i*pri[j]]=-mul[i];
		} 
	}
	for(int i=1;i<maxn;i++)	mul[i]+=mul[i-1];
}
int work(int a,int b)
{
	int lim=min(a,b),ret=0;
	for(int i=1;i<=lim;)
	{
		int end=min(lim,min(a/(a/i),b/(b/i)));
		//cout<<i<<"="<<end<<endl;
		ret+=(mul[end]-mul[i-1])*(a/i)*(b/i);
		i=end+1;
	}
	return ret;	
}
int getfac(int val)
{
	int ret=1;
	for(int i=1;pri[i]<=val&&i<=pn;i++)
	{
		int cnt=1;
		while(val%pri[i]==0)	val/=pri[i],cnt++;
		ret*=cnt;
	}
	return ret;
}
int main()
{
	init();
	cin>>n>>m;
	if(n>m)	swap(n,m);
	for(int i=1;i<=n;i++)	ans+=work(n/i,m/i)*(2*i-1);
	cout<<ans<<endl;
}
