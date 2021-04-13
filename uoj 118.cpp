#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100100;
int n,m,q;
int a[maxn],b[maxn];
int al[maxn],bl[maxn];
int ar[maxn],br[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)	scanf("%d",&b[i]);
	for(int i=2;i<=n;i++)	al[i]=al[i-1]+(a[i-1]!=a[i]);
	for(int i=2;i<=m;i++)	bl[i]=bl[i-1]+(b[i-1]!=b[i]);
	for(int i=n-1;i>=1;i--)	ar[i]=ar[i+1]+(a[i+1]!=a[i]);
	for(int i=m-1;i>=1;i--)	br[i]=br[i+1]+(b[i+1]!=b[i]);
//	for(int i=1;i<=m;i++)	cout<<bl[i]<<"="<<br[i]<<endl;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int xs,ys,xe,ye;	scanf("%d%d%d%d",&xs,&ys,&xe,&ye);
		if(xs>xe)	swap(xs,xe);
		if(ys>ye)	swap(ys,ye);
	//	cout<<xs<<" "<<xe<<" "<<ys<<" "<<ye<<endl;
		printf("%d\n",min(al[xe]-al[xs],al[xs]+ar[xe]+(a[1]!=a[n]))+min(bl[ye]-bl[ys],bl[ys]+br[ye]+(b[1]!=b[m])));
	}
}
