#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int n;
int col[500];
int map[500][500];
int ans=0;
/*
int dfs(int u,int typ)
{
	for(int i=1;i<=typ;i++)
	{
		col[u]=i;
		int flag=0;
		for(int v='A';v<='A'+n-1;v++)
			if(map[u][v])
			{
				if(col[v])
				{
					if(col[u]==col[v])
					{
						flag=1;
						break;
					}
				}
				else
				{
					if(dfs(v,typ)==0)
					{
						flag=1;
						break;
					}
				}
			}	
		if(flag==0)	return 1;
	}
	col[u]=0;
	return 0;
}*/
int dfs(int u,int lim)
{
	if(u=='A'+n)	return 1;
	for(int i=1;i<=lim;i++)
	{
		col[u]=i;
		int flag=0;
		for(int v='A';v<='A'+n-1;v++)	if(map[u][v]==1&&col[v]==col[u])	flag=1;
		if(flag==0)	if(dfs(u+1,lim))	return	1;
		col[u]=0;
	}
	return 0;
}
int main()
{
	while(cin>>n,n)
	{
		memset(map,0,sizeof map);
		for(int i=1;i<=n;i++)
		{
			string s;cin>>s;
			for(int j=2;j<s.size();j++)	map[s[0]][s[j]]=map[s[j]][s[0]]=1;
		}
		
		for(int i=1;i<=n;i++)
		{
			memset(col,0,sizeof col);
			if(dfs('A',i))	{ans=i;break;}
		}
		if(ans==1)	cout<<ans<<" channel needed."<<endl;
		else	cout<<ans<<" channels needed."<<endl;
	}
}
