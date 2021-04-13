#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int a[10000000],b[10000000],n,i;
string st;
int main()
{
	cin>>st;
	n=st.length();
	for(i=0;i<n;i++)
	{
		a[n-i]=st[i]-'0';
	}
	a[0]=n;
	for(i=1;i<=a[0];i++)/*23......33??????89......99,3????9??,89......99=100......00-10..03 so ??*/
	{
	b[i+n-1]+=a[i];
	b[i]+=a[i]*3;
    }
	for(i=1;i<=2*a[i];i++)
	{
		b[i+1]+=a[i]/10;
		a[i]%=10;
	}
	b[0]=2*a[0]+1;
	for(i=b[0];i>=1;i--)
	{
		if(b[i]!=0)
		{
			b[0]=i;
			break;
		}
	}
	for(i=1;i<=a[0];i++)
	{
		a[i+n]=a[i];
		a[i]=0;
	}
	a[0]+=n;
	for(i=1;i<=b[0];i++)
	{
		a[i]-=b[i];
	}
	for(i=1;i<=a[0];i++)
	{
		while(a[i]<0)
//		if(a[i]<0)
		{
			a[i]+=10;
			a[i+1]-=1;
//			if(i==a[0])
		}
	}
	for(i=n;i>=1;i--)
	printf("%d",a[i]);
	return 0;
}
