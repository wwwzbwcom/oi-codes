#include<iostream>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
map <int,int> vis,dir;
int in[10];
int s[5][5];
int x[]={1,-1,0,0};
int y[]={0,0,1,-1};
char o[]={'r','l','d','u'};
char t;
int w,start;
struct P
{
	int y,x;
	P(int a,int b):y(a),x(b){}
};
P check(int now)
{
	P ans(0,0);
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			s[i][j]=now%10,now/=10;
			if(s[i][j]==9) ans=P(i,j);
		}
	return ans;
}
int get()
{
	int ans=0;
	int w=1;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
		//	cout<<ans<<endl;
			ans+=s[i][j]*w;
			w*=10;
		}
	//	cout<<endl;
	}
//	cout<<endl<<endl;
	return ans;
}
void output(int now)
{
	if(vis[now]!=-1) output(vis[now]);
	else return;
	cout<<o[dir[now]];
}
void bfs()
{
	queue <int> q,t;
	q.push(start);
	t.push(0);
	vis[start]=-1;
	while(!q.empty())
	{
		int now=q.front();q.pop();
		int tc=t.front();t.pop();
	
		if(now==987654321){ output(now); return;}
	//	cout<<now<<"="<<endl;
	//	getchar();
		P p=check(now);
		
		for(int i=0;i<4;i++)
		{
			if(s[p.y+y[i]][p.x+x[i]])
			{
				swap(s[p.y+y[i]][p.x+x[i]],s[p.y][p.x]);
				int nxt=get();
				if(vis[nxt]==0)
				{
					q.push(nxt);
					t.push(tc+1);
					vis[nxt]=now;
					dir[nxt]=i;
				}
				swap(s[p.y+y[i]][p.x+x[i]],s[p.y][p.x]);
			}
		}
	}
}
int main()
{
	for(int i=0;i<9;i++)
	{
		cin>>t;
		if(t=='x') in[i]=9;
		else in[i]=t-48;
	}
	w=1,start=0;
	for(int i=0;i<9;i++)
	{
		start+=in[i]*w;
		w*=10;
	}
	bfs();
} 
