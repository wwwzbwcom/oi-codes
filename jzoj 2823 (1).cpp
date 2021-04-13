#include<algorithm>
#include<iostream>
using namespace std;
int gn,n;
int sto[20];
int ans;
int sum;
void dfs(int p,int a,int b,int c,int lef)
{
	if(b+lef<a)	return;
	if(c+lef<=a||c+lef<=b)	return;
	if((c+lef)*(c+lef)<a*a+b*b)	return; 
	int t=(a+b+lef);
	
	if(t%2)
	{
		if(((t+1)/2*(t+1)/2)/2<ans)	return; 
	}
	else
	{
		if((t/2*t/2)/2<ans)	return;
	}
	
	//if(p==6&a==8&&b==15&&c==10)	cout<<p<<" "<<a<<" "<<b<<" "<<c<<endl;
	if(a>0&&b>0&&c>0&&a*a+b*b==c*c)	ans=max(ans,a*b/2);
	if(p==n)	return;
	dfs(p+1,a,b,c,lef-sto[p]);
	dfs(p+1,a+sto[p],b,c,lef-sto[p]);
	dfs(p+1,a,b+sto[p],c,lef-sto[p]);
	dfs(p+1,a,b,c+sto[p],lef-sto[p]);
}
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n;
		ans=-1;	sum=0;
		for(int i=0;i<n;i++)	cin>>sto[i],sum+=sto[i],sto[i]=-sto[i];
		sort(sto,sto+n);
		for(int i=0;i<n;i++)	sto[i]=-sto[i];
		dfs(0,0,0,0,sum);
		cout<<ans<<endl;
	}
}
