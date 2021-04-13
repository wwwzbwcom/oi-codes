#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
class Con
{
	public:
		int lis[3][50],lin[3];
		Con()
		{
			memset(lis,0,sizeof lis);
			memset(lin,0,sizeof lin);
		}
		bool operator ==(const Con &in)const
		{
			for(int i=0;i<3;i++)
			{
				if(lin[i]!=in.lin[i])	return 0;
				for(int j=0;j<lin[i];j++)
					if(lis[i][j]!=in.lis[i][j])	return 0;
			}
			return 1;
		}
		void output()
		{
			for(int i=0;i<3;i++)
			{
				cout<<i<<" "<<lin[i]<<":=  ";
				for(int j=0;j<lin[i];j++)	cout<<lis[i][j]<<" ";
				cout<<endl;
			}
			cout<<"================="<<endl;
		}
}cur,end;
int dfs(int p)
{
//	cout<<p<<"==========="<<endl;
//	cur.output();
	int ans=0;
	if(cur==end)	ans=1;
	if(p==m)	return ans;
	
	for(int i=0;i<3;i++)	if(cur.lin[i]!=0)
		for(int j=0;j<3;j++)
			if(cur.lin[j]==0||cur.lis[i][cur.lin[i]-1]<cur.lis[j][cur.lin[j]-1])
			{
				cur.lin[i]--;	cur.lis[j][cur.lin[j]++]=cur.lis[i][cur.lin[i]];
			//	cout<<i<<" "<<j<<endl;
				ans+=dfs(p+1);
				cur.lin[j]--;	cur.lis[i][cur.lin[i]++]=cur.lis[j][cur.lin[j]]; 
			}
	return ans;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int val;	cin>>val;	val--;
		cur.lis[val][cur.lin[val]++]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int val;	cin>>val;	val--;
		end.lis[val][end.lin[val]++]=i;
	}
//	cur.output();	end.output();
	for(int i=0;i<3;i++)	reverse(cur.lis[i],cur.lis[i]+cur.lin[i]),reverse(end.lis[i],end.lis[i]+end.lin[i]);
//	cur.output();	end.output();
	cout<<dfs(0)<<endl;
}
