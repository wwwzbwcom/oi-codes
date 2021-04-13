#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=10005;
class Query
{
	public:
		int l,r,p;
		Query()
		{
			l=r=p=0;
		}
		Query(int li)
		{
			l=li;	r=0;	p=0;
		}
		bool operator <(const Query	&in)const
		{
			return l<in.l;
		}
}que[maxn][1010];
int p,m;
char str[maxn];
int len;
int cnt[maxn];
int ans[1010];
int main()
{
	cin>>p;
	cin>>str+1;
	len=strlen(str+1);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int li,ri;	cin>>li>>ri;
		que[ri][cnt[ri]].l=li;
		que[ri][cnt[ri]].r=ri;
		que[ri][cnt[ri]].p=i;
		cnt[ri]++;
	}
	for(int i=1;i<=len;i++)	sort(que[i],que[i]+cnt[i]);
//	for(int i=0;i<cnt[6];i++)	cout<<i<<" "<<que[6][i].l<<"="<<que[6][i].r<<endl;
	for(int i=1;i<=len;i++)
	{
		int cur=0,tmp=0;
		for(int j=i;j<=len;j++)
		{
			cur=(cur*10+(str[j]-'0'))%p;
			if(cur==0)	tmp++;
			int pos=upper_bound(que[j],que[j]+cnt[j],Query(i))-que[j];
			for(int k=0;k<pos;k++)	ans[que[j][k].p]+=tmp;
		}
	}
	for(int i=1;i<=m;i++)	cout<<ans[i]<<endl;	
}
