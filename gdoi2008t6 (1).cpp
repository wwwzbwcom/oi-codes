#include<iostream>
#include<cstring>
using namespace std;
const int oo=999999999;
char s[10000];
int aim,len;
int ans;
int idx(char a)
{
	return a-'0';
}
void dfs(int now,int cnt,int total,int cur,int last)
{
	if(cnt>ans) return;
	if(total>aim) return;
	if(now==len) {if(total+cur*last==aim) ans=min(ans,cnt); return;}
	
	dfs(now+1,cnt,total,cur*10+idx(s[now]),last);
	dfs(now+1,cnt+1,total+cur*last,idx(s[now]),1);
	dfs(now+1,cnt+1,total,idx(s[now]),cur*last);
}
int main()
{
	while(cin>>s>>aim)
	{
		if(aim==-1) break;
		ans=oo;
		len=strlen(s);
		dfs(1,0,0,idx(s[0]),1);
		if(ans==oo)	cout<<-1<<endl;
		else	cout<<ans<<endl;
	}
}
