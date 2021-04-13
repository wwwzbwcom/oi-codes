#include<iostream>
using namespace std;
struct CLO
{
	CLO(){};
	CLO(int ti,int li,int ri,int di){t=ti;l=li;r=ri;d=di;}
	int t,l,r,d;
}clo[2100];
int n,len;
int sto[2100][2100];
int sum[2100][2100];
int mod(int a,int p)
{
	return (a%p+p)%p;
}
void addcloud(int t,int l,int r,int d)
{
	int ltr=r-l+1;
	int siz=2*(len+d);
	int sta=mod(-t,siz);
	if(d==1)
	{
		l=mod(sta+l,siz);
		r=mod(sta+r,siz);
	}
	else
	{
		l=mod(sta-l,siz);
		r=mod(sta-r,siz);
	}
	if(l<=r)	for(int i=l;i<=r;i++)	sto[ltr][i]++;
	else
	{
		for(int i=l;i<siz;i++)	sto[ltr][i]++;
		for(int i=0;i<=r;i++)	sto[ltr][i]++;
	}
	for(int i=1;i<siz;i++)	sum[ltr][i]=sum[ltr][i-1]+sto[ltr][i];
}
int getsum(int l,int r,int d)
{
	int siz=(d+len)*2;
	if(l<=r)
	{
		if(l==0)	return sum[d][r];
		else	return sum[d][r]-sum[d][l-1];
	}
	else
	{
		if(l==0)	return sum[d][siz-1]+sum[d][r];
		else		return sum[d][siz-1]-sum[d][l-1]+(sum[d][r]);
	}
}
int query(int t,int l,int r)
{
	int ans=0;
	for(int i=1;i<=len;i++)
	{
		int siz=2*(len+i);
		int sta=mod(-t,siz);
		ans+=getsum(mod(sta+l,siz),mod(sta+r,siz),i);
		ans+=getsum(mod(sta-l,siz),mod(sta-r,siz),i);
	}
	return ans;
}
void delcloud(int t,CLO c)
{
	int d=c.d;
	int siz=2*(len+d);
	int l=(c.l+t-c.t,siz);
	int r=(c.r+t-c.t,siz);
	if(l<=r)	for(int i=l;i<=r;i++)	sto[d][i]++;
	else
	{
		for(int i=l;i<siz;i++)	sto[d][i]++;
		for(int i=0;i<=r;i++)	sto[d][i]++;
	}
	for(int i=1;i<siz;i++)	sum[d][i]=sum[d][i-1]+sto[d][i];
}
int main()
{
	cin>>n>>len;
//	len++;
	for(int i=1;i<=n;i++)
	{
		int cmd;cin>>cmd;
		if(cmd==1)
		{
			int t,c,l,r,d;	cin>>t>>c>>l>>r>>d;
			addcloud(t,l,r,d);
			clo[c]=CLO(t,l,r,d);
		}
		if(cmd==2)
		{
			int t,l,r;	cin>>t>>l>>r;
			cout<<query(t,l,r)<<endl;
		}
		if(cmd==3)
		{
			int t,c;	cin>>t>>c;
			delcloud(t,clo[c]);
		}
	}
}
