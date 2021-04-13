#include<iostream>
#include<cstring>
using namespace std;
int a,b;
int x,y,c;
int t;
int flag=0;
int vis[100][100];
int main()
{
	cin>>a>>b;
	if(a*b%2==1)	t=0,cout<<"First"<<endl,cout<<a/2<<" "<<b/2<<endl;
	else	t=1,cout<<"Second"<<endl;
	memset(vis,-1,sizeof vis);
	while(cin>>x>>y>>c)
	{
		if(vis[x][y]==-1&&vis[x-1][y]!=c&&vis[x+1][y]!=c&&vis[x][y-1]!=c&&vis[x][y+1]!=c)
		{
			cout<<a-x+1<<" "<<b-y+1<<" "<<(c^t)<<endl;
			vis[a-x+1][b-y+1]=(c^t);
			vis[x][y]=c;
		}
		else
		{
			cout<<"Buwanle"<<endl;
			return 0;
		}
	}

}
