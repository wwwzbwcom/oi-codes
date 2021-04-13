#include<algorithm> 
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=2e6+100;
const int mod=19930726;
class Hash
{
	public:
		char str[maxn];	int len;
		long long mul[maxn],has[maxn];
		void build()
		{
			mul[0]=1;	for(int i=1;i<=len;i++)	mul[i]=mul[i-1]*129;
			has[0]=0;	for(int i=1;i<=len;i++)	has[i]=has[i-1]*129+str[i-1];
		}
		long long getkey(int p,int l)
		{
			p++;
			return has[p+l-1]-has[p-1]*mul[l];
		}
		
}f,b;
int rng[maxn];
void gethwn()
{
	for(int i=0;i<f.len;i++)
	{
		int l=0,r=min(i+1,f.len-i),ans=0;
		while(l<=r)
		{
			int m=(l+r)/2;
			if(f.getkey(i,m)==b.getkey(f.len-i-1,m))	ans=m,l=m+1;
			else	r=m-1;
		}
		rng[i]=ans*2-1;
	}
}
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=((long long)ans*ans)%(long long)mod;
		if(b%2==0)	return ans;
		else	return ((long long)ans*a)%(long long)mod;
	 } 
}
int n;
long long k;
int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",f.str);
	f.len=n;
	b.len=f.len;
	memcpy(b.str,f.str,sizeof f.str);
	reverse(b.str,b.str+b.len);
	f.build();	b.build();
	gethwn();
	//
	sort(rng,rng+f.len);
	//for(int i=0;i<f.len;i++)	cout<<i<<" "<<rng[i]<<endl; 
	//cout<<"==============="<<endl;
	rng[f.len]=rng[f.len-1]+1;
	long long cnt=0;
	int ans=1;
	for(int i=f.len-1;i>=0;i--)
	{
		if(i!=0&&rng[i]==rng[i-1])	continue;
		else
		{
			for(int j=rng[i];j>rng[i-1];j-=2)
			{
				//cout<<j<<"="<<i<<" "<<cnt<<" "<<f.len-i<<" "<<ans<<endl;
				if(cnt+(f.len-i)<=k)	ans=((long long)ans*qsm(j,f.len-i))%(long long)mod;
				else	ans=((long long)ans*qsm(j,k-cnt))%(long long)mod;
				cnt+=f.len-i;
				if(cnt>=k)	break;
			}
			//cout<<cnt<<endl;
			if(cnt>=k)	break;
		}
	}
	if(cnt>=k)	printf("%d\n",ans);
	else	printf("-1\n");
}
