#include<iostream>
#include<map>
using namespace std;
const int maxn=1100;
class Node
{
	public:
		int ls,rs;
		int lc,rc;
		map <int,int> dyp;
}n[maxn];
int gn;
int nn,xs,ys,mx;
int xl[maxn],xr[maxn],y[maxn];
int dfs(int p,int x)
{
//	cout<<p<<" "<<x<<endl; 
	if(n[p].dyp.find(x)!=n[p].dyp.end())	return n[p].dyp[x];
	int ans=1e9;
	if(n[p].ls!=-1)
	{
		if(n[p].ls==0)	ans=min(ans,(x-xl[p])+n[p].lc);
		else	ans=min(ans,(x-xl[p])+n[p].lc+dfs(n[p].ls,xl[p]));
	}
	if(n[p].rs!=-1)
	{
		if(n[p].rs==0)	ans=min(ans,(xr[p]-x)+n[p].rc);
		else	ans=min(ans,(xr[p]-x)+n[p].rc+dfs(n[p].rs,xr[p]));
	}
//	cout<<p<<"="<<x<<" "<<ans<<endl;
	n[p].dyp[x]=ans;
	return ans;
}
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>nn>>xs>>ys>>mx;
		for(int i=1;i<=nn;i++)	cin>>xl[i]>>xr[i]>>y[i];
		for(int i=1;i<=nn;i++)	n[i].dyp.clear();
		for(int i=1;i<=nn;i++)
		{
			int p;
			p=-1;
			for(int j=1;j<=nn;j++)	if(i!=j)
			{
				if(y[j]<y[i]&&y[j]+mx>=y[i]&&xl[j]<=xl[i]&&xl[i]<=xr[j])
					if(p==-1||y[j]>y[p])	p=j;
			}
			if(p==-1)
			{
				if(y[i]<=mx)	n[i].ls=0,n[i].lc=y[i];
				else	n[i].ls=-1,n[i].lc=0;
			}
			else	n[i].ls=p,n[i].lc=y[i]-y[p];
		
			p=-1;
			for(int j=1;j<=nn;j++)	if(i!=j)
			{
				if(y[j]<y[i]&&y[j]+mx>=y[i]&&xl[j]<=xr[i]&&xr[i]<=xr[j])
					if(p==-1||y[j]>y[p])	p=j;
			}
			if(p==-1)
			{
				if(y[i]<=mx)	n[i].rs=0,n[i].rc=y[i];
				else	n[i].rs=-1,n[i].rc=0;
			}
			else	n[i].rs=p,n[i].rc=y[i]-y[p];
		}
		//for(int i=1;i<=nn;i++)	cout<<n[i].ls<<" "<<n[i].rs<<endl;
		int p=-1;
		for(int i=1;i<=nn;i++)
		{
			if(y[i]<=ys&&y[i]+mx>=ys&&xl[i]<=xs&&xs<=xr[i])
				if(p==-1||y[i]>y[p])	p=i;
		}
		if(p==-1)	cout<<ys<<endl;
		else	cout<<dfs(p,xs)+ys-y[p]<<endl;
	}
}
