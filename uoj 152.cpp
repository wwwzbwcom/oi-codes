#include<algorithm>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
const int maxn=10100;
int n;
int a[maxn];
int b[maxn],bn;
int ans[maxn*1000][2],an;
void output(int a,int b)
{
	ans[an][0]=a+1;
	ans[an][1]=b+1;
	an++;
}
void work(int l,int r,int p)
{
	if(l==r)	return;
	int m=(l+r)/2;
	//cout<<l<<"="<<m<<"="<<r<<endl;
	for(int i=l;i<=m;i++)	output(p,p^1);
	//cout<<"="<<endl;
	reverse(a+l,a+m+1);
	work(l,m,p^1);	work(m+1,r,p);
	
	for(int i=l;i<=m;i++)	output(p^1,2);
	for(int i=m+1;i<=r;i++)	output(p,p^1);
	reverse(a+l,a+m+1);	reverse(a+m+1,a+r+1);
	
	int lp=l,rp=m+1;	bn=0;
	while(lp<=m&&rp<=r)
	{
	//	cout<<a[lp]<<"="<<a[rp]<<endl;
		if(a[lp]>=a[rp])	b[++bn]=a[lp],lp++,output(2,p);
		else				b[++bn]=a[rp],rp++,output(p^1,p);
	}
	while(lp<=m)	b[++bn]=a[lp],lp++,output(2,p);
	while(rp<=r)	b[++bn]=a[rp],rp++,output(p^1,p);
	reverse(b+1,b+bn+1);
	memcpy(a+l,b+1,sizeof(int)*bn);
}
int tmp[maxn];
void check()
{
	stack <int> sta[4];
	for(int i=n;i>=1;i--)	sta[1].push(tmp[i]);
	for(int i=0;i<an;i++)
	{
		sta[ans[i][1]].push(sta[ans[i][0]].top());
		printf("%d=%d %d\n",ans[i][0],ans[i][1],sta[ans[i][0]].top());
		sta[ans[i][0]].pop();
	}
	while(!sta[1].empty())
	{
		printf("%d=\n",sta[1].top());
		sta[1].pop();
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]),tmp[i]=a[i];
	work(1,n,0);
	printf("%d\n",an);
	for(int i=0;i<an;i++)	printf("%d %d\n",ans[i][0],ans[i][1]);
	//check();
}
