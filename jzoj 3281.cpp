#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int gn,m,n;
char map[50][50];
int liy[10],lix[10],ln;
int opt[10]; 
class ZKW
{
	private:
		class Edge
		{
			public:
				int v,c,f;
				int nxt;
		}e[50*50*10*2];
		int pre[50*50*2*10],en;
		int vis[50*50*2*10];
		int pfee;
		int dfs(int u,int lc)
		{
		//	cout<<u<<endl;
			if(u==end)
			{
				tfee+=pfee*lc;
				return lc;
			}
			int nc=0;
			vis[u]=1;
			for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c,f=e[i].f;
				if(!vis[v]&&c&&!f)
				{
					//if(v==end)	cout<<u<<"=="<<endl;
					int cc=min(lc-nc,c);
					cc=dfs(v,cc);
				//	cout<<u<<" "<<v<<" "<<cc<<endl; 
					e[i].c-=cc;
					e[i^1].c+=cc;
					nc+=cc;
				}
			}
			return nc;
		}
		bool getdis()
		{
			int mni=1e9;
			for(int u=0;u<=end;u++)	if(vis[u])
			{
			//	if(u==20)	cout<<u<<"!!"<<endl; 
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c,f=e[i].f;
				//	if(u==20)	cout<<v<<"=="<<c<<"=="<<f<<endl;
					if(!vis[v]&&c)	mni=min(mni,f);
				}
			}
		//	cout<<mni<<endl;
			if(mni==1e9)	return 0;
			pfee+=mni;
			for(int u=0;u<=end;u++)	if(vis[u])
				for(int i=pre[u];i!=-1;i=e[i].nxt)
					e[i].f-=mni,e[i^1].f+=mni;
			return 1;
		}
	public:
		int sta,end;
		int flo,tfee;
		void init()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v,int c,int f)
		{
			e[en].v=v;e[en].c=c;e[en].f= f;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].f=-f;e[en].nxt=pre[v];pre[v]=en++;
		}
		void zkw()
		{
			do
			{
				int t;
				do
				{
				//	cout<<tfee<<"@@@"<<endl;
					memset(vis,0,sizeof vis);
					t=dfs(sta,1e9);
				//	cout<<t<<"~~"<<endl;
					flo+=t;
				}while(t);
			}while(getdis());
		}
}ba,zk;
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>n>>m;
		ba.init();	zk.init(); 
		ln=0;
		ba.sta=n*m*2+1;
		ba.end=n*m*2+2;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cin>>map[i][j];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(map[i][j]!='#')
				{
					if(map[i][j]=='.')	ba.addedge((i*m+j)*2,(i*m+j)*2+1,1,1);
					else
					{
						ba.addedge((i*m+j)*2,(i*m+j)*2+1,1,0);
						liy[ln]=i;	lix[ln]=j;	ln++;
					}
				}
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				for(int p=-1;p<=1;p++)
					for(int q=-1;q<=1;q++)	if(abs(p)+abs(q)==1&&0<=i+p&&i+p<n&&0<=j+q&&j+q<m)
						if(map[i][j]!='#'&&map[i+p][j+q]!='#')
						{
						//	cout<<i<<" "<<j<<" "<<i+p<<" "<<j+q<<endl;
							ba.addedge((i*m+j)*2+1,((i+p)*m+(j+q))*2,1,0);
						}
			}
	//	cout<<"==================="<<endl;
		for(int i=0;i<ln;i++)
		{
			opt[i]=-1;
			for(int j=0;j<ln;j++)	if(i!=j)
				if(map[liy[i]][lix[i]]==map[liy[j]][lix[j]])	opt[i]=j;
		}
		int ans=1e9;
	//	for(int i=0;i<ln;i++)	cout<<i<<" "<<liy[i]<<" "<<lix[i]<<endl;
		if(ln%2==0)
		{
			for(int i=0;i<(1<<ln)-1;i++)
			{
				int t=0;
				for(int j=0;j<ln;j++)	if((i&(1<<j))==(1<<j))	t++;
				if(t==ln/2)
				{
					int flag=0;
					for(int j=0;j<ln;j++)	if(opt[j]!=-1)	if(((i&(1<<j))==(1<<j)&&(i&(1<<opt[j]))==0)||((i&(1<<j))==0&&(i&(1<<opt[j]))==(1<<opt[j])))	flag=1;
					if(flag==0)
					{
						//cout<<i<<"="<<endl;
						zk=ba;
						for(int j=0;j<ln;j++)
						{
							if((i&(1<<j))==(1<<j))	zk.addedge(zk.sta,(liy[j]*m+lix[j])*2,1,0);
							else	zk.addedge((liy[j]*m+lix[j])*2+1,zk.end,1,0);
						}
					//	cout<<zk.flo<<endl;
						zk.zkw();
					//	cout<<i<<"="<<zk.flo<<"="<<zk.tfee<<endl;
						if(zk.flo==ln/2)	ans=min(ans,zk.tfee);
					}
				}
				
			}
		}
		if(ans==1e9)	cout<<-1<<endl;
		else	cout<<ans<<endl;
	}
}
