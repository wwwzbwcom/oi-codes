#include<iostream>
using namespace std;
int vis[21][21][21];
int dyp[21][21][21];
int dfs(int w,int h,int m)
{
	if(vis[w][h][m])	return	dyp[w][h][m];
	vis[w][h][m]=1;
	
	if(h%m==0)	dyp[w][h][m]=w*(h/m);	else	dyp[w][h][m]=w*((int)(h/m)+1);
	
	for(int i=1;i<w;i++)
		for(int j=1;j<m;j++)
			dyp[w][h][m]=min(dyp[w][h][m],max(dfs(i,h,j),dfs(w-i,h,m-j)));
	
	for(int i=1;i<h;i++)
		for(int j=1;j<m;j++)
			dyp[w][h][m]=min(dyp[w][h][m],max(dfs(w,i,j),dfs(w,h-i,m-j)));
	
	return dyp[w][h][m];
}
int main()
{
	while(1)
	{
		int w,h,m;	cin>>w>>h>>m;
		if(!w)	break;
		cout<<dfs(w,h,m)<<endl;
	}
}
