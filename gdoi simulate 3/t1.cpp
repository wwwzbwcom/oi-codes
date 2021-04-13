#include<set>
#include<cstdio>
#include<algorithm> 
using namespace std;
const int maxn=100100;
struct Seg
{
	int l,r;
	int c;
	bool operator <(const Seg &in)const
	{
		if(l==in.l)	return r<in.r;
		else	return l<in.l;
	}
}seg[maxn];
int n;
int sto[maxn*2],sc;
set <int> sta[maxn*2],end[maxn*2]; 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&seg[i].l,&seg[i].r);	seg[i].r++;
		sto[sc++]=seg[i].l;	sto[sc++]=seg[i].r;
	}
	sort(sto,sto+sc);
	sc=unique(sto,sto+sc)-sto;
	for(int i=1;i<=n;i++)
	{
		seg[i].l=lower_bound(sto,sto+sc,seg[i].l)-sto+1;
		seg[i].r=lower_bound(sto,sto+sc,seg[i].r)-sto+1;
		sta[seg[i].l].insert(i);
		end[seg[i].r].insert(i);
	}
	int cur=0,flag=0;
	for(int i=1;i<=2*n;i++)
	{
		for(set<int>::iterator j=end[i].begin();j!=end[i].end();j++)
		{
			if(seg[*j].c==0)	cur--;
			if(seg[*j].c==1)	cur++;
		}
		for(set<int>::iterator j=sta[i].begin();j!=sta[i].end();j++)
		{
			if(cur<=0)	seg[*j].c=0,cur++;
			else	seg[*j].c=1,cur--;
		}
		if(abs(cur)>1)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)	printf("-1\n");
	else	for(int i=1;i<=n;i++)	printf("%d ",seg[i].c);
}
