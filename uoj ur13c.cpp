#include<iostream>
#include<cstring>
using namespace std;
const int maxn=2e5;
bool boo[maxn];
int pri[maxn],pn;
long long l,r;
long long ans;
long long val[maxn*100];
int fir[maxn*100],sec[maxn*100];
void init()
{
	boo[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=maxn)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
int main()
{
	init();
	cin>>l>>r;
//	cout<<r-l<<endl;
	for(long long i=l;i<=r;i++)	val[i-l]=i;
//	cout<<val[r-l]<<endl;
	for(int i=1;i<=pn;i++)
	{
		for(long long j=(l/pri[i]);j<=(r/pri[i]);j++)
		{
			long long cur=j*pri[i];
			if(!(l<=cur&&cur<=r))	continue;
			
			int cnt=0;
			while(val[cur-l]%pri[i]==0)	val[cur-l]/=pri[i],cnt++;
			
			if(cnt==1)	sec[cur-l]=fir[cur-l],fir[cur-l]=pri[i];
			else	if(cnt>=2)	fir[cur-l]=sec[cur-l]=pri[i];
			
		//	if(cur==r)	cout<<cur<<" "<<pri[i]<<" "<<cnt<<" "<<val[cur-l]<<" "<<fir[cur-l]<<" "<<sec[cur-l]<<endl;
		}
	}
	for(long long i=l;i<=r;i++)
	{
		if(val[i-l]!=1)	sec[i-l]=fir[i-l],fir[i-l]=val[i-l];
		//cout<<i<<" "<<fir[i-l]<<" "<<sec[i-l]<<endl,getchar();
	}
	for(long long i=l;i<=r;i++)	ans+=sec[i-l];//cout<<i<<" "<<sec[i-l]<<endl;
	cout<<ans<<endl;
}
