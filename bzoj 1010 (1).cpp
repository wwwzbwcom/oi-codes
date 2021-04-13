#include<iostream>
#include<cstring>
using namespace std;
long long n,l;
long long len[100000];
long long sum[100000];
long long f[100000];
long long p[100000],q[100000];
long long x[100000],y[100000];
long long a[100000],b[100000];
long long L,R;
int main()
{	
	cin>>n>>l;
	for(int i=1;i<=n;i++)	cin>>len[i];
	for(int i=1;i<=n;i++)	sum[i]=sum[i-1]+len[i];
	
	R=1;
	for(int i=1;i<=n;i++)
	{
		p[i]=sum[i]+i-l-1,q[i]=sum[i]+i;
		a[i]=-2*p[i],b[i]=1;
		while(L+1<R&&(a[i]*x[L]+b[i]*y[L])>=(a[i]*x[L+1]+b[i]*y[L+1]))	L++;
		f[i]=(a[i]*x[L]+b[i]*y[L])+p[i]*p[i];
		long long xc=q[i],yc=f[i]+q[i]*q[i];
		while(L+1<R&&(y[R-1]-y[R-2])*(xc-x[R-2])>(yc-y[R-2])*(x[R-1]-x[R-2]))	R--;
		x[R]=xc,y[R]=yc,R++;
	}
	cout<<f[n]<<endl;
}
