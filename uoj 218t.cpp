#include<iostream>
#include<stack>
using namespace std;
const int maxn=1010;
int n,m,ty;
int lastans; 
stack <int> sta[maxn];
int qrysum(int l,int r)
{
	int ans=0;
	for(int i=l;i<=r;i++)	if(!sta[i].empty())	ans+=sta[i].top(); 
	return ans;
}
void pop(int l)
{
	if(!sta[l].empty())sta[l].pop();
}
void push(int l,int r,int x)
{
	for(int i=l;i<=r;i++)	sta[i].push(x);
	
}
int main()
{
	cin>>n>>m>>ty;
	for(int i=1;i<=m;i++)
	{
		int cmd,l,r,x;
		cin>>cmd;
		if(cmd==1)
		{
			cin>>l>>r;	l=(l+lastans*ty)%n+1;	r=(r+lastans*ty)%n+1;
			if(l>r)	swap(l,r);
			lastans=qrysum(l,r);
			cout<<lastans<<"=="<<endl;
		}
		if(cmd==2)
		{
			cin>>l;	l=(l+lastans*ty)%n+1;
			pop(l);
		}
		if(cmd==3)
		{
			cin>>l>>r>>x;	l=(l+lastans*ty)%n+1;	r=(r+lastans*ty)%n+1;
			if(l>r)	swap(l,r);
			push(l,r,x);
		}
	}
}
