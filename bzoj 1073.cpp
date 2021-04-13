#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<queue>
using namespace std;

const int inf = 1e8;
struct EDG
{
	EDG(int vi,int ci){v=vi;c=ci;}
	int v,c;
};
vector <EDG> e[150],r[150];
bool flag;

struct INFO
{
	INFO(int ui,int di,int expi,string rti){u=ui;d=di;exp=expi;rt=rti;}
	int u,d,exp;
	string rt;
	bool operator<(const INFO &in)const
	{
		if(!flag)
		{
			if(d+exp==in.d+in.exp)	return rt>in.rt;
			return d+exp>in.d+in.exp;
		}
		else
		{
			return d > in.d;
		}
	}
};
int n,m,k,a,b;
int vis[150];
int exp[150];
priority_queue <INFO>	q;


void getexp()
{
	memset(vis,0,sizeof vis);
	while(!q.empty())	q.pop();
    flag = true;	
	q.push(INFO(b,0,0,""));
	
	while(!q.empty())
	{
		INFO cur=q.top();q.pop();
		int u=cur.u,d=cur.d;
		if(vis[u]==0)
		{
			vis[u]=1;
			exp[u]=d;
		//	cout<<u<<"===================="<<d<<endl;
			for(int i=0;i<r[u].size();i++)
			{
				int v=r[u][i].v,c=r[u][i].c;
				if(vis[v]==0)	q.push(INFO(v,d+c,0,""));
			}
		//	cout<<endl;
		}
	}
}
void dijstra()
{	
	while(!q.empty())	q.pop();
    flag = false;	
	string tmp;	tmp+=(char)a;
	q.push(INFO(a,0,exp[a],tmp));
	
	int cnt=0;
	int mark=0;
	
	while(!q.empty())
	{
		INFO cur=q.top();q.pop();
		int u=cur.u,d=cur.d;
		string rt=cur.rt;
		if(cur.exp==inf) break;
		if(u==b)
		{
			cnt++;
			
			if(cnt==k)
			{
				for(int i=0;i<rt.size()-1;i++)	cout<<(int)rt[i]<<"-";
				cout<<(int)rt[rt.size()-1]<<endl;
				mark=1;
				break;
			}
		}
		for(int i=0;i<e[u].size();i++)
		{
			int v=e[u][i].v,c=e[u][i].c;
			int flag=0;
			for(int j=0;j<rt.size();j++)	if(rt[j]==v)	flag=1;
			if(flag==0)	q.push(INFO(v,d+c,exp[v],rt+(char)v));
		}
	}
	if(mark==0)	cout<<"No";
}
int main()
{
//	if("abc"<"ac")	cout<<"1111111111111111"<<endl;
	cin>>n>>m>>k>>a>>b;
	for(int i=1;i<=n;i++)	exp[i]=inf;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		e[u].push_back(EDG(v,c));
		r[v].push_back(EDG(u,c));
	}
	getexp();
//	for(int i=1;i<=n;i++)	cout<<i<<" "<<exp[i]<<endl;
	dijstra();
	while(1);
}
