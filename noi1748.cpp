#include<iostream>
using namespace std;
int nxt[1000];
int bck[1000];
int main()
{
	int n,m;
	while(cin>>n>>m,n,m)
	{
		for(int i=1;i<=n;i++)	nxt[i]=i+1,bck[i]=i-1;
		nxt[n]=1;
		bck[1]=n;
		int cur=1;
		int cnt=1;
		while(nxt[cur]!=cur)
		{ 
			//cout<<cur<<" "<<cnt<<endl;
			//getchar();
			if(cnt==m)
			{
				cnt=0;
				nxt[bck[cur]]=nxt[cur];
				bck[nxt[cur]]=bck[cur];
			}
			cnt++;
			cur=nxt[cur];
		}
		cout<<cur<<endl;
	}
}
