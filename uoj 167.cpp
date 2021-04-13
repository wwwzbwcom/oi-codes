#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
const int mod=998244353;
int n,m;
struct Node
{
	int sto[3][100];
	int cnt[3];
	int pac;
	bool operator <(const Node &in)const
	{
		if(pac<in.pac)	return 1;
		else	if(pac>in.pac)	return 0;
		for(int i=0;i<3;i++)
		{
			if(cnt[i]<in.cnt[i])	return 1;
			else
			{
				if(cnt[i]>in.cnt[i])	return 0;
				else
				{ 
					for(int j=0;j<cnt[i];j++)
						if(sto[i][j]<in.sto[i][j])	return 1;
						else	if(sto[i][j]>in.sto[i][j])	return 0;
				}
			}
		}
	}
	bool operator ==(const Node &in)const
	{
		if(pac!=in.pac)	return 0;
		for(int i=0;i<3;i++)
		{
			if(cnt[i]!=in.cnt[i])	return 0;
			else
			{
				for(int j=0;j<cnt[i];j++)	if(sto[i][j]!=in.sto[i][j])	return 0;
			}
		}
		return 1;
	}
};
Node sta,end;
map <Node,int> dyp;
map <Node,int> vis;
bool judge(const Node &a,const Node &b)
{
	for(int i=0;i<3;i++)
		{
			if(a.cnt[i]!=b.cnt[i])	return 0;
			else	for(int j=0;j<a.cnt[i];j++)	if(a.sto[i][j]!=b.sto[i][j])	return 0;
		}
	return 1;
}
int dfs(Node cur)
{
	if(cur.pac>m)	return 0;
	if(vis[cur]==1)	return dyp[cur];
	int ans=judge(cur,end);
	Node tmp;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)	if(i!=j&&cur.cnt[i]>0)
		{
			if(cur.cnt[j]==0||cur.sto[i][cur.cnt[i]-1]<cur.sto[j][cur.cnt[j]-1])
			{
				tmp=cur;
				tmp.cnt[i]--;
				tmp.sto[j][tmp.cnt[j]++]=tmp.sto[i][tmp.cnt[i]];
				tmp.pac++;
				ans+=dfs(tmp);
				ans%=mod;
			}
		}
	dyp[cur]=ans;
	return ans;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;	cin>>x;	x--;
		sta.sto[x][sta.cnt[x]++]=i;
	}
	sta.pac=0;
	for(int i=1;i<=n;i++)
	{
		int x;	cin>>x;	x--;
		end.sto[x][end.cnt[x]++]=i;
	}
	for(int i=0;i<3;i++)
	{
		reverse(sta.sto[i],sta.sto[i]+sta.cnt[i]);
		reverse(end.sto[i],end.sto[i]+end.cnt[i]);
	}
	cout<<dfs(sta)<<endl;
}
