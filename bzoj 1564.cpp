#include<cstdio>
#include<iostream>
#include<algorithm> 
using namespace std;
const int maxn=100;
int n,k;
class Point
{
	public:
		int val,wei,fre;
		bool operator <(const Point &in)const
		{
			return val<in.val;
		}
}p[maxn];
int tmp[maxn];
long long dyp[maxn][maxn][maxn];
int vis[maxn][maxn][maxn];
long long	ans=1e16; 
long long dfs(int le,int re,int w)
{
	if(vis[le][re][w])	return dyp[le][re][w];
	vis[le][re][w]=1;
	if(le>re)	return dyp[le][re][w]=0;
	
	dyp[le][re][w]=1e16;
	long long sum=0;
	for(int i=le;i<=re;i++)	sum+=p[i].fre;
	for(int i=le;i<=re;i++)
	{
		dyp[le][re][w]=min(dyp[le][re][w],dfs(le,i-1,w)+dfs(i+1,re,w)+k+sum);
		if(p[i].wei>=w)	dyp[le][re][w]=min(dyp[le][re][w],dfs(le,i-1,p[i].wei)+dfs(i+1,re,p[i].wei)+sum);
	}
	return dyp[le][re][w];
}
int main()
{
	cout<<3.14*((15.0/2)*(15.0/2)+(15.0/2)*15+(20.0/2)*15)-3.14*(1.5/2)*(1.5/2)<<endl;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)	scanf("%d",&p[i].val);
	for(int i=1;i<=n;i++)	scanf("%d",&p[i].wei),tmp[i]=p[i].wei;
	for(int i=1;i<=n;i++)	scanf("%d",&p[i].fre);
	sort(p+1,p+n+1); 
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++)	p[i].wei=lower_bound(tmp,tmp+n,p[i].wei)-tmp;
//	for(int i=1;i<=n;i++)	cout<<i<<" "<<p[i].val<<" "<<p[i].wei<<" "<<p[i].fre<<endl; 
	for(int i=1;i<=n;i++)	ans=min(ans,dfs(1,n,i));
	printf("%lld\n",ans);
}
