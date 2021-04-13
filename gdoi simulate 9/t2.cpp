//#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=1000000;
struct BCJ
{
	struct Node
	{
		int pos;
		map <int,int> fat;
	}n[maxn];
	inline void merge(int u,int v,int t)
	{
	//	cout<<getfat(u,t)<<" "<<getfat(v,t)<<endl;
	//	cout<<getfat(u,t)<<" "<<getfat(v,t)<<endl; 
		if(getfat(u,t)!=getfat(v,t))	n[getfat(u,t)].fat[t]=getfat(v,t);
	}
	inline int query(int u,int v,int t)
	{
	//	cout<<u<<"="<<v<<"="<<t<<" "<<getfat(u,t)<<" "<<getfat(v,t)<<endl;
	//	cout<<u<<"="<<v<<"="<<t<<" "<<getfat(u,t)<<" "<<getfat(v,t)<<endl;
	//	cout<<u<<"="<<v<<"="<<t<<" "<<getfat(u,t)<<" "<<getfat(v,t)<<endl;
		if(getfat(u,t)==getfat(v,t))	return 1;	else	return 0;
	}
	int getfat(int u,int t)
	{
	//	cout<<u<<endl;
		
		if(n[u].fat.find(t)==n[u].fat.end())	n[u].fat[t]=1;
		else
		{
			if(n[u].fat[t]==u)	return n[u].fat[t];
			return	n[u].fat[t]=getfat(n[u].fat[t],t);
		}
		
		map <int,int>:: iterator it;
		it=n[u].fat.find(t);
		
		if(it==n[u].fat.begin())
		{
			n[u].fat.erase(it);
			return n[u].fat[t]=u;
		}
	//	if(t==1)	cout<<u<<" "<<it->first<<"=="<<it->second<<endl;
		n[u].fat.erase(it--);
	//	if(t==1)	cout<<u<<" "<<it->first<<"=="<<it->second<<" "<<endl;
	//	if(t==1)	cout<<getfat(it->second,t)<<endl;
		if(it->second==u)	return n[u].fat[t]=u;
		return n[u].fat[t]=getfat((it->second),t);
	}
}b;
int n,m;
int tim=0;
int cva[maxn];
int lie[maxn];
int main()
{
//	freopen("history6.in","r",stdin);
//	freopen("out.txt","w",stdout);
//	freopen("data2.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		char cmd[2];	scanf("%s",cmd);	int x,y,t;
		if(cmd[0]=='K')	scanf("%d",&x),cva[tim]=x,lie[tim]=0;
		if(cmd[0]=='R')
		{
			tim++;	cva[tim]=cva[tim-1];	lie[tim]=lie[tim-1];
			scanf("%d%d",&x,&y);
			if(lie[tim]==1)	x=((x+cva[tim])%n+n)%n,y=((y+cva[tim])%n+n)%n;
		//	cout<<x<<"~"<<y<<" "<<lie[tim]<<endl;
			b.merge(x,y,tim);
		}
		if(cmd[0]=='T')
		{
			scanf("%d%d%d",&x,&y,&t);
		//	cout<<b.query(x,y,tim)<<endl;
			if(b.query(x,y,tim)&&(!b.query(x,y,tim-t))) 	lie[tim]=0,printf("Y\n");
			else	lie[tim]=1,printf("N\n");
		}
	//	cout<<"="<<b.getfat(5,1)<<endl;
	//	cout<<"===================="<<endl; 
	}
//	b.getfat(0,0);
}
