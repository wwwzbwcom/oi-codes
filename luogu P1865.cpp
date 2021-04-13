#include<iostream>
using namespace std;
int n,m;
int book[10001000];
int prime[10001000],cnt=0;
void pt()
{
	for(int i=1;i<=1e7;i++)	book[i]=1;
	book[1]=0;
	for(int i=2;i<=1e7;i++)
	{
		if(book[i])	prime[cnt++]=i;
		for(int j=0;j<cnt;j++)
		{
			if(i*prime[j]>1e7)	break;
			book[i*prime[j]]=0;
			if(i%prime[j]==0)	break;
		}
	}
	for(int i=1;i<=1e6;i++)	book[i]=book[i-1]+book[i];
}
int main()
{
	pt();
	return 0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		cin>>l>>r;
		if(l<=0||r<=0||l>m||r>m)	cout<<"Crossing the line"<<endl;
		else	cout<<book[r]-book[l-1]<<endl;
	}
}
