#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200100;
const int mod=1000000007;
int mul[maxn];
int rev[maxn];
struct HW
{
	void init()
	{
		mul[0]=1;	for(int i=1;i<maxn;i++)	mul[i]=(mul[i-1]*130ll)%(long long)mod;
		rev[0]=1;	for(int i=1;i<maxn;i++)	rev[i]=(rev[i-1]*515384619ll)%(long long)mod;
	}
	struct Hash
	{
		char str[maxn];
		int  has[maxn];
		int  len;
		void build()
		{
			len=strlen(str+1);
			has[0]=0;	for(int i=1;i<=len;i++)	has[i]=((long long)has[i-1]+(long long)str[i]*mul[i])%(long long)mod;
		}
		int getkey(int p,int l)
		{
			return (((has[p+l-1]-has[p-1])%mod+mod)%mod*(long long)rev[p-1])%(long long)mod;
		}
	}f,b;
	int work(int lq,int rq)
	{
		int ans=1e9;
		for(int i=lq;i<=rq;i++)
		{
			int	l=1,r=min(i-lq+1,rq-(i+1)+1),len=0,tmp=0;
			while(l<=r)
			{
				int m=(l+r)/2;
			//	cout<<f.len-i+1<<" "<<i+1<<" "<<m<<" "<<b.getkey(b.len-i+1,m)<<" "<<f.getkey(i+1,m)<<endl;
				if(b.getkey(b.len-i+1,m)==f.getkey(i+1,m))	len=m,l=m+1;
				else	r=m-1;
			}
			//n[i].l=len;	n[i].p=i;
			if(len==0)	tmp=rq-lq+1;
			else
			{
				int lc=i-len+1,rc=(i+1)+len-1;
				tmp+=(lc-1)-lq+1;
				tmp+=rq-(rc+1)+1;
				tmp+=work(lc,i)+1;	
			}
			ans=min(ans,tmp);
		}
		return ans;
	}
}hw;
int gn;
int main()
{
	hw.init();
	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		scanf("%s",hw.f.str+1); 
		int len=strlen(hw.f.str+1);
		memcpy(hw.b.str+1,hw.f.str+1,len);
		reverse(hw.b.str+1,hw.b.str+len+1);
		hw.f.build();	hw.b.build();
	//	cout<<hw.f.getkey(4,1)<<endl;
	//	for(int i=1;i<=len;i++)	cout<<hw.f.has[i]<<" "<<hw.b.has[i]<<" "<<rev[i]<<endl;
		printf("%d\n",hw.work(1,len));
	}
}
