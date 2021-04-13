#include<iostream>
#include<map>
using namespace std;
long long ans[1000][2],an;
map <long long,bool> boo;
long long gcd(long long a,long long b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
void work(long long a,long long b)
{
	if(a<=b)	return;
	if(a<=0)	return;
	if(b<=0)	return;
	if(boo[a-b])	return;
	ans[an][0]=a,	 ans[an][1]=b,	an++;
	boo[a-b]=1;
}
void work_gcd(long long a,long long b)
{
	if(a<b)	swap(a,b);
	if(b==0)	return;
	long long t=a/b;
	long long tmp=b;
	long long cur=0;
	while(t)
	{
		if(t%2)	work(a-cur,tmp),cur+=tmp;
		t/=2;
		if(t==0)	break;
		work(a,tmp);
		work(a-tmp,tmp);
		work(a,a-2*tmp);
		tmp*=2;
	}
	
	work_gcd(b,a%b);
}
int main()
{
	long long a,b,c;	cin>>a>>b>>c;
	if(a<b)	swap(a,b);
	
	long long g=gcd(a,b);
	if(a<c||(a-c)%g!=0)	cout<<"-1"<<endl;
	else
	{
		work_gcd(a,b);
		
		long long g=gcd(a,b);
		
		long long t=(a-c)/g;
		long long tmp=g;
		long long cur=0;
		
		while(t)
		{
			if(t%2)	work(a-cur,tmp),cur+=tmp;
			t/=2;
			if(t==0)	break;
			work(a,tmp);
			work(a-tmp,tmp);
			work(a,a-2*tmp);
			tmp*=2;
		}
		
		cout<<an<<endl;
		for(long long i=0;i<an;i++)	cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
	}
}
