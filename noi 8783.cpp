#include<iostream>
#include<string>
using namespace std;
int n;
string s[100];
char start;
int map[100][100];
int vis[100];
int ans=0;
void dfs(int len,int tail)
{
	ans=max(ans,len);
	for(int i=0;i<n;i++)
		if(vis[i]<2&&map[tail][i]>0)
		{
			vis[i]++;
			dfs(len+map[tail][i],i);
			vis[i]--;
		}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>s[i];
	cin>>start;
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			map[i][j]=0;
			int len=min(s[i].size(),s[j].size());
			if(s[i].substr(s[i].size()-len,len)!=s[j].substr(0,len)&&s[i].substr(0,len)!=s[j].substr(s[j].size()-len,len))
			{
				for(int k=1;k<len;k++)
				{
					if(s[i].substr(s[i].size()-k,k)==s[j].substr(0,k))
					{
						map[i][j]=s[j].size()-k;
						break;
					}
				}
			}
		}


	for(int i=0;i<n;i++)
		if(s[i][0]==start)
		{
			vis[i]++;
			dfs(s[i].size(),i);
			vis[i]--;
		}
	cout<<ans<<endl;
} 
