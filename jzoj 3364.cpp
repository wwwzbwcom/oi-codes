#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=1e8;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[10000*10];
	int pre[10000],en;
	int lev[10000];
	int blo[10000];
	int cst,cen;
	int sst,sen;
	int nst,nen;
	void addedge(int u,int v,int c)
	{
	//	cout<<u<<" "<<v<<" "<<c<<endl;
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	bool bfs()
	{
		memset(lev,-1,sizeof lev);	queue <int> que;
		lev[nst]=1;	que.push(nst);
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==-1&&c&&blo[v]==0)
				{
					lev[v]=lev[u]+1;
					if(v==nen)	return 1;
					que.push(v);
				}
			}
		}
		return 0;
	}
	int dfs(int u,int lc)
	{
		if(u==nen)	return lc;
		int nc=0;
		for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(lev[v]==lev[u]+1&&c&&blo[v]==0)
			{
				int cc=min(lc-nc,c);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc==0)	lev[u]=-1;
		return nc;
	}
	int dinic()
	{
		int ans=0;
		while(bfs())	ans+=dfs(nst,oo);
		return ans;
	}
}d;
int n,m;
char map[100][100];
int col[100][100];
int fou[10000];
int fin[10000];
int sum;
int ans;
int main()
{
	cin>>n>>m;
	d.cst=n*m;
	d.cen=n*m+1;
	d.sst=n*m+2;
	d.sen=n*m+3; 
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			cin>>map[i][j];
			col[i][j]=(i%2+j%2)%2;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)	if(map[i][j]=='.')
		{
			if(col[i][j]==0)
			{
				if(i==0||i==n-1||j==0||j==m-1)	d.addedge(d.cst,i*m+j,1),fou[d.cst]+=1,fin[i*m+j]+=1;
				else	fou[d.cst]+=2,fin[i*m+j]+=2;
				for(int p=-1;p<=1;p++)
					for(int q=-1;q<=1;q++)	if(abs(p)+abs(q)==1&&map[i+p][j+q]=='.')
						d.addedge(i*m+j,(i+p)*m+j+q,1);
			}
			else
			{
				if(i==0||i==n-1||j==0||j==m-1)	d.addedge(i*m+j,d.cen,1),fou[i*m+j]+=1,fin[d.cen]+=1;
				else	fou[i*m+j]+=2,fin[d.cen]+=2;
			}
		}
	d.addedge(d.cen,d.cst,oo);
	for(int i=0;i<n*m+2;i++)
	{
		if(fin[i]-fou[i]>0)	d.addedge(d.sst,i,fin[i]-fou[i]),sum+=fin[i]-fou[i];
		if(fin[i]-fou[i]<0)	d.addedge(i,d.sen,-fin[i]+fou[i]);
	}
	d.nst=d.sst;
	d.nen=d.sen;
	if(sum!=d.dinic())	cout<<"-1"<<endl;
	else
	{
		d.nst=d.cst;
		d.nen=d.cen;
	//	d.blo[d.sst]=1;
	//	d.blo[d.sen]=1;
		int t=d.dinic();
		for(int i=d.pre[d.cst];i!=-1;i=d.e[i].nxt)	if(d.e[i].v!=d.sst)
		{
		//	cout<<d.e[i].c<<"="<<d.e[i].v<<endl;
			if(d.e[i].c==1)		ans++;
		}
	//	cout<<"========================="<<endl;
		for(int i=d.pre[d.cen];i!=-1;i=d.e[i].nxt)	if(d.e[i].v!=d.sen&&d.e[i].v!=d.cst)
		{
		//	cout<<d.e[i^1].c<<"="<<d.e[i^1].v<<" "<<d.e[i].v<<endl;
			if(d.e[i^1].c==1)	ans++;
		}
		cout<<ans/2<<endl;
	}
}
