#include<iostream>
#include<stack>
using namespace std;
int an,bn;
int ast[600],bst[600];
int dyp[600][600];
int ans;
int pa,pb;
stack <int> sta;
int main()
{
	cin>>an;
	for(int i=0;i<an;i++)	cin>>ast[i];
	cin>>bn;
	for(int i=0;i<bn;i++)	cin>>bst[i];
	for(int i=0;i<an;i++)
		for(int j=0;j<bn;j++)
			if(ast[i]==bst[j])	dyp[i][j]=1; 
	for(int i=0;i<an;i++)
		for(int j=0;j<bn;j++)	if(ast[i]==bst[j])
		{
			for(int p=0;p<i;p++)
				for(int  q=0;q<j;q++)
					if(ast[p]==bst[q]&&ast[p]<ast[i])
						dyp[i][j]=max(dyp[i][j],dyp[p][q]+1);
			if(ans<dyp[i][j])
			{
				ans=dyp[i][j];
				pa=i;
				pb=j;
			}
		}
	cout<<ans<<endl;
	while(1)
	{
		if(dyp[pa][pb]==0)	break;
		sta.push(ast[pa]);
		int flag=1;
		for(int i=0;i<pa;i++)
			for(int  j=0;j<pb;j++)
				if(ast[i]==bst[j]&&dyp[i][j]+1==dyp[pa][pb])
				{
					pa=i;
					pb=j;
					flag=0;
					break;
				}
		if(flag)	break;
	}
	while(!sta.empty())
	{
		cout<<sta.top()<<" ";
		sta.pop(); 
	}
}
