#include<iostream>
using namespace std;
const int maxn=5000;
int n,m;
double har[maxn];
double num[maxn];
double sco[maxn];
double getans(int sta,int end)
{
	for(int i=sta;i<=end;i++)
	{
		num[i]=har[i]*num[i-1]+(1-har[i]);
		sco[i]=har[i]*(num[i]*num[i]+num[i]+1)+(1-har[i])*num[i-1];
	}
	return sco[end];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>har[i];
	for(int i=1;i<=m;i++)
	{
		int cmd;	cin>>cmd;
		if(cmd==0)
		{
			int x,y;	cin>>x>>y;
			cout<<getans(x,y)<<"="<<endl;
		}
		else
		{
			int x;	double y;	cin>>x>>y;
			har[x]=y;
		}
	} 
}
