#include<iostream>
using namespace std;
int book[200][200];
int main()
{
	int yn,xn,num;	cin>>yn>>xn>>num;
	int cnt=0;
	for(int i=0;i<num;i++)
	{
		int y,x,r,mod;	cin>>y>>x>>r>>mod;
		if(mod==1)	cnt++;
		for(int i=max(y-r/2,1);i<=min(y+r/2,yn);i++)
			for(int j=max(x-r/2,1);j<=min(x+r/2,xn);j++)
				if(mod==0)	book[i][j]=-1e9;
				else	book[i][j]++;
	}
	int ans=0;
	for(int i=1;i<=yn;i++)
		for(int j=1;j<=xn;j++)
			if(book[i][j]==cnt)
				ans++;
	cout<<ans;
}
