#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int mod=100000;
int idx(char a)
{
	if(a=='A') return 0;
	if(a=='C') return 1;
	if(a=='T') return 2;
	if(a=='G') return 3;
}
struct Matrix
{
	long long s[200][200];
	int x,y;
	Matrix(int a,int b):x(a),y(b){memset(s,0,sizeof s);}
	Matrix operator*(const Matrix in) const 
	{
		Matrix ans(x,in.y);
		for(int a=0;a<x;a++)
			for(int b=0;b<in.y;b++)
				for(int c=0;c<y;c++)
					ans.s[a][b]+=s[a][c]*in.s[c][b],
					ans.s[a][b]=ans.s[a][b]%mod;
		return ans;
	}
	Matrix operator^(int in)
	{
		in--;
		Matrix ans=*this;
		while(in>=1)
		{
			if(in%2==1) ans=ans* *this;
			*this=*this * *this;
			in/=2;
		}
		return ans;
	}
};
struct AC
{
	int next[1000][4];
	int fail[1000];
	int end[1000];
	int nn,root;
	int newnode()
	{
		for(int i=0;i<4;i++) next[nn][i]=-1;
		end[nn]=0;
		return nn++;
	}
	void init()
	{
		nn=0;
		root=newnode();
		fail[root]=root;
	}
	void insert(char s[])
	{
		int len=strlen(s);
		int now=root;
		for(int i=0;i<len;i++)
		{
			int cur=idx(s[i]);
			if(next[now][cur]==-1)	next[now][cur]=newnode();
			now=next[now][cur] ;
		}
		end[now]=1;
	}
	void build()
	{
		queue <int> q;
		for(int i=0;i<4;i++)
		{
			if(next[root][i]==-1) next[root][i]=root;
			else fail[next[root][i]]=root,q.push(next[root][i]);
		}
		while(!q.empty())
		{
			int now=q.front();q.pop();
			for(int i=0;i<4;i++)
			{
				if(next[now][i]==-1) next[now][i]=next[fail[now]][i];
				else fail[next[now][i]]=next[fail[now]][i],q.push(next[now][i]);
				
				if(end[ next[fail[now] ][i] ]==1) end[next[now][i]]=1;
			}
		}
	}
	Matrix work()
	{
		Matrix store(nn,nn);
		for(int i=0;i<nn;i++)
			if(end[i]==0)
				for(int j=0;j<4;j++)
					if(end[next[i][j]]==0) store.s[i][ next[i][j] ]++;
		return store;
	}
}ac;
int n,m;
char s[100];
int main()
{
	scanf("%d%d",&n,&m);
	ac.init();
	for(int i=1;i<=n;i++)
		scanf("%s",s),ac.insert(s);
	ac.build();
	Matrix ans=ac.work();
/*	for(int i=0;i<ans.x;i++)
	{
		for(int j=0;j<ans.y;j++)
			cout<<ans.s[i][j]<<" ";
		cout<<endl;
	}
	*/
	ans=ans^m;
	long long output=0;
	for(int i=0;i<ans.y;i++)
	{
		output+=ans.s[0][i];
	//	cout<<ans.s[0][i]<<endl;
		output%=mod;
	}
	printf("%lld",output);
}


